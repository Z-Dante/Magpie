#include "pch.h"
#include "App.h"
#include "Utils.h"
#include "GraphicsCaptureFrameSource.h"
#include "DwmSharedSurfaceFrameSource.h"
#include "GDIOverDXGIFrameSource.h"
#include "GDIFrameSource.h"


extern std::shared_ptr<spdlog::logger> logger;

const UINT App::_WM_DESTORYHOST = RegisterWindowMessage(L"MAGPIE_WM_DESTORYHOST");


App::~App() {
	MagUninitialize();
	Windows::Foundation::Uninitialize();
}

bool App::Initialize(HINSTANCE hInst) {
	SPDLOG_LOGGER_INFO(logger, "Initializing App");

	_hInst = hInst;

	// 初始化 COM
	HRESULT hr = Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);
	if (FAILED(hr)) {
		SPDLOG_LOGGER_CRITICAL(logger, MakeComErrorMsg("Initialize COM Failed", hr));
		return false;
	}
	SPDLOG_LOGGER_INFO(logger, "COM initialized");

	// 注册主窗口类
	_RegisterHostWndClass();

	// 供隐藏光标和 MagCallback 抓取模式使用
	if (!MagInitialize()) {
		SPDLOG_LOGGER_ERROR(logger, MakeWin32ErrorMsg("MagInitialize Failure"));
	}

	SPDLOG_LOGGER_INFO(logger, "App Initialization successful");
	return true;
}

bool App::Run(
	HWND hwndSrc,
	const std::string& effectsJson,
	int captureMode,
	bool noCursor,
	bool adjustCursorSpeed,
	bool showFPS,
	bool disableRoundCorner,
	int frameRate,
	bool disableLowLatency
) {
	_hwndSrc = hwndSrc;
	_captureMode = captureMode;
	_noCursor = noCursor;
	_adjustCursorSpeed = adjustCursorSpeed;
	_showFPS = showFPS;
	_frameRate = frameRate;
	_disableLowLatency = disableLowLatency;

	// 每次进入全屏都要重置
	_nextTimerId = 1;
	
	SetErrorMsg(ErrorMessages::GENERIC);

	_srcClientRect = Utils::GetClientScreenRect(_hwndSrc);
	if (_srcClientRect.right == 0 || _srcClientRect.bottom == 0) {
		SPDLOG_LOGGER_CRITICAL(logger, "Failed to get source window");
		return false;
	}

	SPDLOG_LOGGER_INFO(logger, fmt::format("Source window size：{}x{}",
		_srcClientRect.right - _srcClientRect.left, _srcClientRect.bottom - _srcClientRect.top));

	if (!_CreateHostWnd()) {
		SPDLOG_LOGGER_CRITICAL(logger, "Failed to create main window");
		return false;
	}

	_renderer.reset(new Renderer());
	if (!_renderer->Initialize()) {
		SPDLOG_LOGGER_CRITICAL(logger, "Failed to initialize Renderer, cleaning up");
		DestroyWindow(_hwndHost);
		_Run();
		return false;
	}
	
	switch (captureMode) {
	case 0:
		_frameSource.reset(new GraphicsCaptureFrameSource());
		break;
	case 1:
		_frameSource.reset(new DwmSharedSurfaceFrameSource());
		break;
	case 2:
		_frameSource.reset(new GDIOverDXGIFrameSource());
		break;
	case 3:
		_frameSource.reset(new GDIFrameSource());
		break;
	default:
		SPDLOG_LOGGER_CRITICAL(logger, "Unknown capture mode, terminating");
		DestroyWindow(_hwndHost);
		_Run();
		return false;
	}
	

	if (!_frameSource->Initialize(_srcFrameSize)) {
		SPDLOG_LOGGER_CRITICAL(logger, "Failed to initialize FrameSource, terminating");
		DestroyWindow(_hwndHost);
		_Run();
		return false;
	}

	if (!_renderer->InitializeEffectsAndCursor(effectsJson)) {
		SPDLOG_LOGGER_CRITICAL(logger, "Failed to initialize effect, terminating");
		DestroyWindow(_hwndHost);
		_Run();
		return false;
	}

	// 合适时禁用窗口圆角
	bool roundCornerDisabled = false;
	if (disableRoundCorner && _frameSource->HasRoundCornerInWin11()) {
		const auto& version = Utils::GetOSVersion();
		bool isWin11 = Utils::CompareVersion(
			version.dwMajorVersion, version.dwMinorVersion,
			version.dwBuildNumber, 10, 0, 22000) >= 0;

		if (isWin11) {
			INT attr = DWMWCP_DONOTROUND;
			HRESULT hr = DwmSetWindowAttribute(hwndSrc, DWMWA_WINDOW_CORNER_PREFERENCE, &attr, sizeof(attr));
			if (FAILED(hr)) {
				SPDLOG_LOGGER_ERROR(logger, "Failed to disable rounded window corners");
			} else {
				SPDLOG_LOGGER_INFO(logger, "Rounded window corners has been undisabled");
				roundCornerDisabled = true;
			}
		}
	}

	_Run();

	if (roundCornerDisabled) {
		INT attr = DWMWCP_DEFAULT;
		HRESULT hr = DwmSetWindowAttribute(hwndSrc, DWMWA_WINDOW_CORNER_PREFERENCE, &attr, sizeof(attr));
		if (FAILED(hr)) {
			SPDLOG_LOGGER_INFO(logger, "Failed to disable rounded window corners");
		} else {
			SPDLOG_LOGGER_INFO(logger, "Rounded window corners has been undisabled");
		}
	}
	
	return true;
}

void App::_Run() {
	SPDLOG_LOGGER_INFO(logger, "Started receiving window information");

	while (true) {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				// 释放资源
				_ReleaseResources();
				SPDLOG_LOGGER_INFO(logger, "Main window destroyed");
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_renderer->Render();
	}
}

ComPtr<IWICImagingFactory2> App::GetWICImageFactory() {
    if (_wicImgFactory == nullptr) {
        HRESULT hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&_wicImgFactory)
        );

		if (FAILED(hr)) {
			SPDLOG_LOGGER_ERROR(logger, MakeComErrorMsg("Failed to create WICImagingFactory", hr));
			return nullptr;
		}
    }

    return _wicImgFactory;
}

bool App::RegisterTimer(UINT uElapse, std::function<void()> cb) {
	if (!SetTimer(_hwndHost, _nextTimerId, uElapse, nullptr)) {
		SPDLOG_LOGGER_ERROR(logger, MakeWin32ErrorMsg("SetTimer Failed"));
		return false;
	}

	++_nextTimerId;
	_timerCbs.emplace_back(std::move(cb));

	return true;
}

// 注册主窗口类
void App::_RegisterHostWndClass() const {
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = _HostWndProcStatic;
	wcex.hInstance = _hInst;
	wcex.lpszClassName = _HOST_WINDOW_CLASS_NAME;

	if (!RegisterClassEx(&wcex)) {
		// 忽略此错误，因为可能是重复注册产生的错误
		SPDLOG_LOGGER_ERROR(logger, MakeWin32ErrorMsg("Failed to register main window class"));
	} else {
		SPDLOG_LOGGER_INFO(logger, "Main Window Class Registered");
	}
}

// 创建主窗口
bool App::_CreateHostWnd() {
	if (FindWindow(_HOST_WINDOW_CLASS_NAME, nullptr)) {
		SPDLOG_LOGGER_CRITICAL(logger, "Main window already exists");
		return false;
	}

	RECT screenRect = Utils::GetScreenRect(_hwndSrc);
	_hostWndSize.cx = screenRect.right - screenRect.left;
	_hostWndSize.cy = screenRect.bottom - screenRect.top;
	_hwndHost = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT,
		_HOST_WINDOW_CLASS_NAME,
		NULL, WS_CLIPCHILDREN | WS_POPUP | WS_VISIBLE,
		screenRect.left,
		screenRect.top,
		_hostWndSize.cx,
		_hostWndSize.cy,
		NULL,
		NULL,
		_hInst,
		NULL
	);
	if (!_hwndHost) {
		SPDLOG_LOGGER_CRITICAL(logger, MakeWin32ErrorMsg("Failed to create main window"));
		return false;
	}

	SPDLOG_LOGGER_INFO(logger, fmt::format("Main Window Dimensions：{}x{}", _hostWndSize.cx, _hostWndSize.cy));

	// 设置窗口不透明
	if (!SetLayeredWindowAttributes(_hwndHost, 0, 255, LWA_ALPHA)) {
		SPDLOG_LOGGER_ERROR(logger, MakeWin32ErrorMsg("SetLayeredWindowAttributes Failure"));
	}

	if (!ShowWindow(_hwndHost, SW_NORMAL)) {
		SPDLOG_LOGGER_ERROR(logger, MakeWin32ErrorMsg("ShowWindow Failure"));
	}

	SPDLOG_LOGGER_INFO(logger, "Main window created");
	return true;
}

LRESULT App::_HostWndProcStatic(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return GetInstance()._HostWndProc(hWnd, message, wParam, lParam);
}


LRESULT App::_HostWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == _WM_DESTORYHOST) {
		SPDLOG_LOGGER_INFO(logger, "Received MAGPIE_WM_DESTORYHOST message, main window will be destroyed soon");
		DestroyWindow(_hwndHost);
		return 0;
	}

	switch (message) {
	case WM_DESTROY:
	{
		// 有两个退出路径：
		// 1. 前台窗口发生改变
		// 2. 收到_WM_DESTORYMAG 消息
		PostQuitMessage(0);
		return 0;
	}
	case WM_TIMER:
	{
		if (hWnd != _hwndHost || wParam <= 0 || wParam > _timerCbs.size()) {
			break;
		}

		_timerCbs[wParam - 1]();
		return 0;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void App::_ReleaseResources() {
	_frameSource = nullptr;
	_renderer = nullptr;

	// 计时器资源在窗口销毁时自动释放
	_timerCbs.clear();
}
