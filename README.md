# MAGPIE - Forked from https://github.com/Blinue/Magpie
#######################################################################################    
**HOW TO USE:** 

 ☛ Run Magpie and keep in open in the background    
 ☛ Open your game / visual novel in **windowed mode**    
 ☛ Use Alt + F11 hotkeys to upscale your game window using magpie    
 ☛ Modify the ScaleModels.json if you want your very own custom stack of presets to use with Magpie   
 
 NOTE: You'll need to start Magpie as admin if you want to upscale a game that's also running with admin privileges 
 
#######################################################################################    
**SOME COMPARISONS / UPSCALING RESULTS WITH VARIOUS PRESETS:**

* Little Busters English Edition   
Original 720p: https://imgur.com/d44YvuW    
Upscaled: https://imgsli.com/Nzg3NTY    

* Muramasa   
Original (1024x576): https://imgur.com/cLKNMUT    
Upscaled: https://imgsli.com/Nzg3NzM/

* Chaos;Head (Chaotic;Head)    
Original 800x600: https://imgur.com/pscXt9U    
Upscaled: https://imgsli.com/Nzg3NTg/    

* Sengoku Rance   
Original 800x600: https://imgur.com/45CUSTX    
Upscaled: https://imgsli.com/Nzg3NjY    
Original 2: https://imgur.com/26OyiIv    
Upscaled 2: https://imgsli.com/Nzg3Njg    

* Majikoi S
Original 800x600: https://imgur.com/F7cE1cy    
Upscaled: https://imgsli.com/Nzg3NzA    

* Hoshi Ori Yume Mirai
Original 720p: https://imgur.com/fRTG8YQ    
Upscaled: https://imgsli.com/Nzg3NjQ    

* Utawarerumono: Prelude to the Fallen 720p -> 1080p:     
https://imgsli.com/Nzg3NTU

* Daitoshokan no Hitsujikai 720p -> 1080p:     
https://imgsli.com/Nzg3NzQ

* Kinkoi 1080 -> 1440p:     
https://imgsli.com/Nzg3NzY

* Old v0.6.0 ACNet Screenshots from various VNs:     
https://imgur.com/a/lnBpL0q

#######################################################################################    
**RECOMMENDED PRESETS**

1. Anime4K
2. ACNet (RCAS)
3. Anime4K (RCAS)

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

################################## ORIGINAL README #####################################   
# MAGPIE

[![build](https://github.com/Blinue/Magpie/actions/workflows/build.yml/badge.svg)](https://github.com/Blinue/Magpie/actions/workflows/build.yml)
[![All Contributors](https://img.shields.io/github/all-contributors/Blinue/Magpie)](#%E8%B4%A1%E7%8C%AE%E8%80%85-)
[![许可](https://img.shields.io/github/license/Blinue/Magpie)](./LICENSE)

Magpie 可以将任意窗口放大至全屏，支持多种高级缩放算法，包括 Lanczos、[Anime4K](https://github.com/bloc97/Anime4K)、[FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR)、[FSRCNNX](https://github.com/igv/FSRCNN-TensorFlow)等。

主要用于游戏窗口的放大显示，适用于不支持全屏模式，或者内置的全屏模式会使画面模糊的情况。

使用中遇到问题请提交 issue。

☛ [编译指南](https://github.com/Blinue/Magpie/wiki/编译指南)

☛ [FAQ](https://github.com/Blinue/Magpie/wiki/FAQ)

☛ [自定义缩放配置](https://github.com/Blinue/Magpie/wiki/自定义缩放配置)

☛ [贡献指南](https://github.com/Blinue/Magpie/blob/master/CONTRIBUTING.md)

## 使用方法

![窗口截图](img/窗口截图.png)

要放大的窗口位于前台时，按下热键即可全屏显示该窗口，再次按下热键或者切换前台窗口将退出全屏。

以下为配置说明：

#### 热键修改

程序使用[globalmousekeyhook](https://github.com/gmamaladze/globalmousekeyhook)检测热键。

手动输入键值修改为你喜欢的键位（多个键位组合之间用 `+` 连接）

1. 字母使用大写，如 `A` ；数字使用特殊格式，如 `D1` （小键盘数字则为 `NumPad1` ）
2. 功能键的单词首字母大写，如 `Capital` （不能写 `Caps` ）， `F1` ， `PageUp`
3. 个别键位不能作为单独的触发热键，必须与其它键位组合使用，如 `Control` ， `Shift` ， `Alt`
4. 组合键按照前后顺序按下才能正确触发，如 `B+C` （先按住b不松手而后再按下c）

#### 缩放模式

程序预置了多种缩放模式，如果它们不符合你的需求，请[自定义缩放配置](https://github.com/Blinue/Magpie/wiki/自定义缩放配置)。

1. Lanczos：常见的传统插值算法，善于保留锐利的边缘。
2. FSR：[FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR) 的移植，适合缩放 3D 游戏。
3. FSRCNNX：[FSRCNNX](https://github.com/igv/FSRCNN-TensorFlow) 的移植。
4. ACNet：[ACNetGLSL](https://github.com/TianZerL/ACNetGLSL)的移植。适合动画风格的图像和视频放大。
5. Anime4K：开源的高质量的实时动漫缩放/降噪算法。
6. RAVU：见 [About RAVU](https://github.com/bjin/mpv-prescalers#about-ravu)。此预置使用 zoom 变体。
7. Integer Scale：将每个像素放大整数倍，可以完整保留原图像的视觉效果。预置了2x和3x两种放大倍率。

#### 捕获模式

指示程序如何捕获源窗口图像。

1. Graphics Capture：使用 [Screen Capture API](https://docs.microsoft.com/en-us/windows/uwp/audio-video-camera/screen-capture) 捕获窗口，最推荐的方法。此 API 从 Windows 10, v1903 开始提供。
2. GDI：使用 GDI 捕获源窗口。和 Graphics Capture 相比 CPU 占用更少。
3. DwmSharedSurface：使用未公开的 DwmSharedSurface API 捕获窗口。

## 使用提示

1. 如果你设置了 DPI 缩放，而要放大的窗口不支持（表现为画面模糊），建议首先进入该程序的兼容性设置，将“高 DPI 缩放替代”设置为“应用程序”。

   ![高DPI设置](img/高DPI设置.png)

2. 一些游戏支持调整窗口的大小，但只是简单的使用线性缩放，这时请先将其设为原始分辨率。

## 贡献者 ✨

感谢每一位贡献者，你们使 Magpie 变得更好（[emoji key](https://allcontributors.org/docs/en/emoji-key)）：

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/Blinue"><img src="https://avatars.githubusercontent.com/u/34770031?v=4?s=100" width="100px;" alt=""/><br /><sub><b>刘旭</b></sub></a><br /><a href="#maintenance-Blinue" title="Maintenance">🚧</a> <a href="https://github.com/Blinue/Magpie/commits?author=Blinue" title="Code">💻</a> <a href="https://github.com/Blinue/Magpie/pulls?q=is%3Apr+reviewed-by%3ABlinue" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/Blinue/Magpie/commits?author=Blinue" title="Documentation">📖</a> <a href="#question-Blinue" title="Answering Questions">💬</a></td>
    <td align="center"><a href="https://github.com/hooke007"><img src="https://avatars.githubusercontent.com/u/41094733?v=4?s=100" width="100px;" alt=""/><br /><sub><b>hooke007</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=hooke007" title="Documentation">📖</a> <a href="#question-hooke007" title="Answering Questions">💬</a> <a href="#userTesting-hooke007" title="User Testing">📓</a></td>
    <td align="center"><a href="http://palxex.ys168.com"><img src="https://avatars.githubusercontent.com/u/58222?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Pal Lockheart</b></sub></a><br /><a href="#userTesting-palxex" title="User Testing">📓</a></td>
    <td align="center"><a href="https://www.stevedonaghy.com/"><img src="https://avatars.githubusercontent.com/u/1029699?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Steve Donaghy</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=neoKushan" title="Code">💻</a> <a href="#translation-neoKushan" title="Translation">🌍</a></td>
    <td align="center"><a href="http://gyrojeff.top"><img src="https://avatars.githubusercontent.com/u/30655701?v=4?s=100" width="100px;" alt=""/><br /><sub><b>gyro永不抽风</b></sub></a><br /><a href="https://github.com/Blinue/Magpie/commits?author=JeffersonQin" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/ButtERRbrod"><img src="https://avatars.githubusercontent.com/u/89013889?v=4?s=100" width="100px;" alt=""/><br /><sub><b>ButtERRbrod</b></sub></a><br /><a href="#translation-ButtERRbrod" title="Translation">🌍</a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

本项目遵循 [all-contributors](https://github.com/all-contributors/all-contributors) 规范。欢迎任何形式的贡献！
