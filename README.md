# MAGPIE - Forked from https://github.com/Blinue/Magpie

[![build](https://github.com/Z-Dante/Magpie/actions/workflows/build.yml/badge.svg)](https://github.com/Z-Dante/Magpie/actions/workflows/build.yml)
[![All Contributors](https://img.shields.io/github/all-contributors/Blinue/Magpie)](#%E8%B4%A1%E7%8C%AE%E8%80%85-)
[![许可](https://img.shields.io/github/license/Blinue/Magpie)](./LICENSE)

#######################################################################################    
**HOW TO USE:** 

 ☛ Run Magpie and keep it open in the background / minimize to tray   
 ☛ Open the desired game / visual novel in **windowed mode**    
 ☛ Use Alt + F11 hotkeys to upscale your game window using magpie    
 ☛ Modify the ScaleModels.json if you want your very own custom stack of presets to use with Magpie   
 
 NOTE: You'll need to start Magpie as admin if you want to upscale a game that's also running with admin privileges 
 
#######################################################################################    
**SOME COMPARISONS / UPSCALING RESULTS WITH VARIOUS PRESETS:**

* Little Busters English Edition   
  - Original 720p: https://imgur.com/d44YvuW    
  - Upscaled: https://imgsli.com/Nzg3NTY    
* Muramasa 
  - Original (1024x576): https://imgur.com/cLKNMUT 
  - Upscaled: https://imgsli.com/Nzg3NzM/
* Chaos;Head (Chaotic;Head) 
  - Original 800x600: https://imgur.com/pscXt9U 
  - Upscaled: https://imgsli.com/Nzg3NTg/ 
* Sengoku Rance   
  - Original 800x600: https://imgur.com/45CUSTX    
  - Upscaled: https://imgsli.com/Nzg3NjY    
  - Original 2: https://imgur.com/26OyiIv    
  - Upscaled 2: https://imgsli.com/Nzg3Njg    
* Majikoi S
  - Original 800x600: https://imgur.com/F7cE1cy    
  - Upscaled: https://imgsli.com/Nzg3NzA    
* Hoshi Ori Yume Mirai
  - Original 720p: https://imgur.com/fRTG8YQ    
  - Upscaled: https://imgsli.com/Nzg3NjQ    
* Utawarerumono: Prelude to the Fallen 720p -> 1080p:     
  - https://imgsli.com/Nzg3NTU
* Daitoshokan no Hitsujikai 720p -> 1080p:     
  - https://imgsli.com/Nzg3NzQ
* Kinkoi 1080 -> 1440p:     
  - https://imgsli.com/Nzg3NzY
* Old v0.6.0 ACNet Screenshots from various VNs:     
  - https://imgur.com/a/lnBpL0q
* Some Comparison of CRT shaders:      
  - Kichikuou Rance : https://imgsli.com/ODY5MjE/0/1      
  - Ikusa Megami Zero: https://imgsli.com/ODY5MjU/0/1      
  - CPS1 Cadillacs and Dinosaurs: https://imgsli.com/ODcwMzk/0/1     
* Anime4kGAN vs Anime4k 720p -> 1080p:
  - White Album2: https://imgsli.com/ODczODg/2/3 
* Anime4kGAN Restore 720p -> 1080p:
	- Kunado Kokuki 720p -> 1080p: https://imgsli.com/ODc1NTQ/1/5
	- Duel Savior 480p->1080p: https://imgsli.com/ODc2MTE/1/5

#######################################################################################    
**RECOMMENDED PRESETS**

1. Anime4kGAN 
2. Anime4K
3. ACNet (RCAS)

* Anime4k (Light) - Only if you have low end hardware and are facing performance issues.

#######################################################################################    
**RECOMMENDED SETTINGS**

1. "Restore Full Screen When The Source Window Regains Focus" from ZOOM settings if you have a habit of alt-tabbing and don't want to manually zoom back in with the hotkeys
2. "Run at Startup" if you want magpie to start automatically everytime you start your PC. 
3. "Minimize to the System Tray at Startup" with #2 if you want Magpie to start silently

#######################################################################################    
**SOME POINTERS ABOUT THE PRESETS**
* RCAS - Uses the CAS filter from FSR. Higher overall contrast and sharpness. I used this one instead of the standard CAS cause IMO it makes the details stand out a lot more.
* ACNet - ACNet works very well for anime type art, looks very clean with think lines at the cost of some detail loss.
* Anime4k - Direct port of Anime4k v4. Great results for anime type artwork with minimal cost and detail loss. Does not lose any detail like ACNet. However does not look as clean as ACNet either.
* FSRCNNXLineArt - A fast super resolution CNN algorithm. Despite having the word fast in it, it is quite heavy. Looks great for some VNs and bad at others. Produces ringing artifacts.
* Anime4K Denoise - Anime4kspecific denoising upscaler. For noisy sources. Not recommended for VNs. As the name implies it gets rid of noise (and some details too)
* Restore - Anime4kspecific detail enhancement module. very sharp but produces ringing artifacts. The soft variant doesn't have ringing artifact but isn't as sharp either.

#######################################################################################    
**DOWNLOAD**

Head over to the release section - 
https://github.com/Z-Dante/Magpie/releases

Or grab automated builds from - https://github.com/Z-Dante/Magpie/actions (click on the topmost one and select Magpie-Auto-Build)

################################# **ORIGINAL README** ####################################   
# MAGPIE

🌍 **简体中文** | [English](./README_EN.md)

Magpie 可以将任意窗口放大至全屏，内置大量缩放算法/滤镜。主要用于游戏窗口的放大显示，适用于不支持全屏模式，或者内置的全屏模式会使画面模糊的情况。

使用中遇到问题请提交 issue。

:point_right: [编译指南](https://github.com/Blinue/Magpie/wiki/编译指南)

:point_right: [FAQ](https://github.com/Blinue/Magpie/wiki/FAQ)

:point_right: [自定义缩放配置](https://github.com/Blinue/Magpie/wiki/自定义缩放配置)（[示例](https://gist.github.com/hooke007/818ecc88f18e229bca743b7ae48947ad)）

:point_right: [贡献指南](./CONTRIBUTING.md)


## 使用方法

![窗口截图](img/窗口截图.png)

要放大的窗口位于前台时，按下热键即可全屏显示该窗口，再次按下热键或者切换前台窗口将退出全屏。

以下为配置说明：

#### 缩放模式

程序预置了多种缩放模式，如果它们不符合你的需求，请[自定义缩放配置](https://github.com/Blinue/Magpie/wiki/自定义缩放配置)。

1. Lanczos：常见的传统插值算法，善于保留锐利的边缘。
2. FSR：[FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR) 的移植，适合缩放 3D 游戏。
3. FSRCNNX：[FSRCNNX](https://github.com/igv/FSRCNN-TensorFlow) 的移植。
4. ACNet：[ACNetGLSL](https://github.com/TianZerL/ACNetGLSL)的移植。适合动画风格的图像和视频放大。
5. Anime4K：[Anime4K](https://github.com/bloc97/Anime4K) 的移植。此预置使用 Anime4K_Upscale_Denoise_L 变体。
6. RAVU：见 [About RAVU](https://github.com/bjin/mpv-prescalers#about-ravu)。
7. CRT-Geom：最流行的 CRT 滤镜之一，推荐自行配置参数。见 [Emulation General Wiki](https://emulation.gametechwiki.com/index.php/CRT_Geom)。
8. Integer Scale：将每个像素放大整数倍，可以完整保留原图像的视觉效果。预置了2x和3x两种放大倍率。

#### 捕获模式

指示程序如何捕获源窗口图像，它们的适用场景见[捕获模式对比](https://github.com/Blinue/Magpie/wiki/%E6%8D%95%E8%8E%B7%E6%A8%A1%E5%BC%8F%E5%AF%B9%E6%AF%94)。

1. Graphics Capture：使用 [Screen Capture API](https://docs.microsoft.com/en-us/windows/uwp/audio-video-camera/screen-capture) 捕获窗口，最推荐的方法。此 API 从 Win10 v1903 开始提供。
2. Desktop Duplication：使用 [Desktop Duplication API](https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/desktop-dup-api) 捕获窗口，相比 Graphics Capture 可以捕获到更多类型的窗口。此 API 从 Win10 v2004 开始提供。
3. GDI：使用 GDI 捕获源窗口。和 Graphics Capture 相比 CPU 占用更少。
4. DwmSharedSurface：使用未公开的 DwmSharedSurface API 捕获窗口。

#### 热键修改

程序使用 [globalmousekeyhook](https://github.com/gmamaladze/globalmousekeyhook) 检测热键。

手动输入键值修改为你喜欢的键位（多个键位组合之间用 `+` 连接）

1. 字母使用大写，如 `A` ；数字使用特殊格式，如 `D1` （小键盘数字则为 `NumPad1` ）
2. 功能键的单词首字母大写，如 `Capital` （不能写 `Caps` ）， `F1` ， `PageUp`
3. 个别键位不能作为单独的触发热键，必须与其它键位组合使用，如 `Control` ， `Shift` ， `Alt`
4. 组合键按照前后顺序按下才能正确触发，如 `B+C` （先按住b不松手而后再按下c）

## 系统需求

1. Windows 10/11
2. DirectX 功能级别 10
3. [.NET 6 Desktop 运行时](https://dotnet.microsoft.com/en-us/download/dotnet/6.0)
4. [MSVC 2015-2022 运行时](https://docs.microsoft.com/cpp/windows/latest-supported-vc-redist)


## 使用提示

1. 如果你设置了 DPI 缩放，而要放大的窗口没有高 DPI 支持，推荐首先进入该程序的兼容性设置，将“高 DPI 缩放替代”设置为“应用程序”。

   ![高DPI设置](img/高DPI设置.png)

2. 一些游戏支持调整窗口的大小，但只使用简单的缩放算法，这时请先将其设为原始（最佳）分辨率。

## 贡献者 ✨

感谢每一位贡献者，你们使 Magpie 变得更好（[emoji key](https://allcontributors.org/docs/en/emoji-key)）：

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/Blinue"><img src="https://avatars.githubusercontent.com/u/34770031?v=4?s=100" width="100px;" alt=""/><br /><sub><b>刘旭</b></sub></a><br /><a href="#maintenance-Blinue" title="Maintenance">🚧</a> <a href="https://github.com/Blinue/Magpie/commits?author=Blinue" title="Code">💻</a> <a href="https://github.com/Blinue/Magpie/pulls?q=is%3Apr+reviewed-by%3ABlinue" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/Blinue/Magpie/commits?author=Blinue" title="Documentation">📖</a> <a href="#question-Blinue" title="Answering Questions">💬</a></td>
    <td align="center"><a href="https://github.com/hooke007"><img src="https://avatars.githubusercontent.com/u/41094733?v=4?s=100" width="100px;" alt=""/><br /><sub><b>hooke007</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=hooke007" title="Documentation">📖</a> <a href="#question-hooke007" title="Answering Questions">💬</a> <a href="#userTesting-hooke007" title="User Testing">📓</a> <a href="https://github.com/Blinue/Magpie/commits?author=hooke007" title="Code">💻</a></td>
    <td align="center"><a href="http://palxex.ys168.com"><img src="https://avatars.githubusercontent.com/u/58222?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Pal Lockheart</b></sub></a><br /><a href="#userTesting-palxex" title="User Testing">📓</a></td>
    <td align="center"><a href="https://www.stevedonaghy.com/"><img src="https://avatars.githubusercontent.com/u/1029699?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Steve Donaghy</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=neoKushan" title="Code">💻</a> <a href="#translation-neoKushan" title="Translation">🌍</a></td>
    <td align="center"><a href="http://gyrojeff.top"><img src="https://avatars.githubusercontent.com/u/30655701?v=4?s=100" width="100px;" alt=""/><br /><sub><b>gyro永不抽风</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=JeffersonQin" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/ButtERRbrod"><img src="https://avatars.githubusercontent.com/u/89013889?v=4?s=100" width="100px;" alt=""/><br /><sub><b>ButtERRbrod</b></sub></a><br /><a href="#translation-ButtERRbrod" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/0x4E69676874466F78"><img src="https://avatars.githubusercontent.com/u/4449851?v=4?s=100" width="100px;" alt=""/><br /><sub><b>NightFox</b></sub></a><br /><a href="#translation-0x4E69676874466F78" title="Translation">🌍</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/Tzugimaa"><img src="https://avatars.githubusercontent.com/u/4981077?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Tzugimaa</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=Tzugimaa" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/WHMHammer"><img src="https://avatars.githubusercontent.com/u/35433952?v=4?s=100" width="100px;" alt=""/><br /><sub><b>WHMHammer</b></sub></a><br /><a href="#translation-WHMHammer" title="Translation">🌍</a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

本项目遵循 [all-contributors](https://github.com/all-contributors/all-contributors) 规范。欢迎任何形式的贡献！
