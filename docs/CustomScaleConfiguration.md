This document guides you on how to define your own scaling presets. // Translated from [自定义缩放配置.md](https://github.com/Z-Dante/Magpie/blob/master/docs/%E8%87%AA%E5%AE%9A%E4%B9%89%E7%BC%A9%E6%94%BE%E9%85%8D%E7%BD%AE.md) using [DeepL](https://www.deepl.com/translator)

When Magpie starts, it will search for the configuration file  **"ScaleModels.json"** 
in the root directory of where the program is located, and if it is not found, it will
be automatically generated using the program's built-in default
parameters.\
The full contents of the original configuration file can be [found
here](https://github.com/Z-Dante/Magpie/blob/master/Magpie/Resources/BuiltInScaleModels.json),
and the following is an example of the syntax.
```json
[
  {
    "name": "Lanczos",
    "effects": [
      {
        "effect": "Lanczos",
        "scale": [ -1, -1 ]
      },
      {
        "effect": "AdaptiveSharpen",
        "curveHeight": 0.3
      }
    ]
  },
  {
    "name": "FSR",
    "effects": [
      {
        "effect": "FSR_EASU",
        "scale": [ -1, -1 ]
      },
      {
        "effect": "FSR_RCAS",
        "sharpness": 0.87
      }
    ]
  },
  {
    "...": "..."
  }
]
```
The root element of the configuration file is an array, each member of which is a
"scaling preset". A scaling preset is composed of a series of stacked effects that Magpie
applies one by one as it scales. *The configuration file supports json
comments, including line comments* `// `*and block comments* `/**/`*.*

Magpie has a large number of effects built in for being used in various combinations,
most of them provide various parameters to customize its behavior. All of the
effects / shaders are stored in the "effects" folder, and if you know HLSL you can
easily add your own effects / shaders as you please, see [Custom
Effects](https://github.com/Blinue/Magpie/wiki/%E8%87%AA%E5%AE%9A%E4%B9%89%E6%95%88%E6%9E%9C%EF%BC%88MagpieFX%EF%BC%89).

Almost all effects support a **scale parameter**, whose value must be an array
of two elements. ``[ x , y]``  When the values are positive, they indicate the scale/multiplier of
the original length and height; meanwhile if they are negative, they indicate the maximum
equivalent scale/multiplier relative to what screen resolution; when they are 0,
they indicate scaling to completely fill the screen (the screen may be stretched).
The default value for all scale parameters is \[1, 1\], which is the same
as the input size. You can see their application in the
[example.](#example)

Introduction of built-in effects 
---------------------------------

* ACNet: port of [ACNetGLSL.](https://github.com/TianZerL/ACNetGLSL)
    Suitable for scaling of anime style images with strong noise
    reduction effect
  * Output size: twice the input
 
* AdaptiveSharpen: Adaptive sharpening algorithm. This algorithm
    focuses on sharpening the blurred edges in the image, so there is
    less noise, ringing and streaking than the usual
    sharpening algorithm.
  * Output size: same as input
  * Parameters
    * curveHeight: sharpening intensity. Must be greater than
            zero, usually between 0.3 and 2.0. The default value is 1.0.
            
* Anime4K\_3D\_AA\_Upscale\_US and Anime4K\_3D\_Upscale\_US: 3D game
    screen scaling algorithm provided by Anime4K. AA variants have
    anti-aliasing capabilities.
  * Output size: twice the input

* Anime4K\_Denoise\_Bilateral\_Mean,
    Anime4K\_Denoise\_Bilateral\_Median and
    Anime4K\_Denoise\_Bilateral\_Mode: noise reduction algorithms
    provided by Anime4K, using the mean, median and plural, respectively
  * Output size: same as input
  * Parameters
    * intensitySigma: Noise reduction intensity. Must be greater
            than zero. The default value is 0.1.

* Anime4K\_Restore\_M, Anime4K\_Restore\_L, and Anime4K\_Restore\_VL:
    algorithms provided by Anime4K for restoring anime lines, with
    sequentially higher performance requirements
  * Output size: same as input
* Anime4K\_Thin\_HQ: Algorithm provided by Anime4K to refine the lines
    of anime images
  * Output size: same as input
  * Parameters
    * strength: the strength of each iteration, which must be
            greater than zero. The default value is 0.6.
    * iterations: number of iterations, must be an integer greater
            than zero. The default value is 1. Decreasing the strength
            and increasing iterations will improve the picture quality,
            but will decrease the speed.

* Anime4K\_Upscale\_S, Anime4K\_Upscale\_L,
    Anime4K\_Upscale\_Denoise\_S, Anime4K\_Upscale\_Denoise\_L and
    Anime4K\_Upscale\_GAN\_x2\_S: Animation-style image scaling
    algorithms provided by Anime4K. The Denoise variant includes noise
    reduction, the GAN variant is in the experimental stage and can
    retain more details
  * Output size: twice the input

* Anime4K\_Upscale\_S\_Lite: Lighter version of Anime4K\_Upscale\_S.
    Faster, but may have quality loss. Suitable for users with
    under-performing graphics cards.
  * Output size: twice the input

* Bicubic and Bicubic\_Lite: bicubic (bi-cubic)
    interpolation algorithm. lite variants are faster but may have
    quality loss for users with insufficient graphics card performance
  * Output size: depends on the scale parameter Best when used
        for downscaling.
  * Parameters
    * scale: scale, the value must be an array with two elements.
    * paramB: filter parameter B, must be between 0 and 1. The
            default value is 0.333333. Too large a value will blur
    * paramC: filter parameter C, must be between 0 and 1. The
            default value is 0.333333. Too large a value will
            generate ringing. Different variants of the algorithm can be
            implemented by freely combining different BC values, for
            example: Mitchell (B=C≈0.333333), Catmull-Rom (B=0 C=0.5),
            bicubic Photoshop (B=0 C=0.75), Spline ( B=1 C=0)

* CAS: A port of
    [FidelityFX-CAS.](https://github.com/GPUOpen-Effects/FidelityFX-CAS)
    Lightweight sharpening effects
  * Output size: same as input
  * Parameters
        * sharpness: must be between 0 and 1. The default value is 0.4.
* CRT_Easymode: easy to configure lightweight CRT shader.
  * Output size: depends on the scale parameter
  * Parameters
    * scale: scale parameter scale
    * sharpnessH: horizontal sharpness. The default value is 0.5.
    * sharpnessV: vertical sharpness. The default value is 1.
    * maskStrength: the strength of the mask. The default value is 0.3.
    * maskDotWidth: must be an integer from 1 to 100. The default value is 1.
    * maskDotHeight: must be an integer from 1 to 100. The default value is 1.
    * maskStagger: must be an integer between 0 and 100. The default value is 0.
    * maskSize: must be an integer between 1 and 100. The default value is 1.
    * scanlineStrength: The value range is 0~1. The default value is 1.
    * scanlineBeamWidthMin: The range is 0.5~5. The default value is 1.5. 
    * scanlineBeamWidthMax: The default value is 1.5. The default value is 1.5. 
    * scanlineBeamWidthMax: The value range is 0.5~5. The default value is 1.5. 
    * scanlineBeamWidthMax: The value range is 0.5~5.The default value is 1.5. 
    * scanlineBrightMin: The value range is 0~1. The default value is 0.35. 
    * scanlineBrightMax: The value range is 0.5~5.The default value is 0.65. 
    * scanlineBrightMax: The value range is 0~1. The default value is 0.65.
    * scanlineCutoff: must be an integer between 1~1000. The default value is 400.
    * gammaInput: the value range is 0.1~5. The default value is 2. The default value is 1.8. 
    * gammaOutput: The value range is 0.1~5. The default value is 1.8.
    * brightBoost: Used to boost the brightness. The default value is 1.2.
    * dilation: Boolean type. The default value is true.
* CRT_Geom: One of the most popular CRT shaders, designed to emulate the Arcade machine. see [Emulation General Wiki](https://emulation.gametechwiki.com/index.php/CRT_Geom).
  * Output size: depends on the scale parameter
  * Parameter
    * scale: scale parameter
    * CRTGamma: The value range is 0.1~5. Default value is 2.4.
    * monitorGamma: range 0.1~5. default is 2.2. 
    * distance: range 0.1~5. default is 2.2.
    * distance: the range of 0.1~3. The default value is 1.5.
    * curvature: if or not to simulate screen curvature. Boolean. The default value is true.
    * radius: the radius of curvature. The default value is 2.
    * cornerSize: the range of 0.001~1. The default value is 0.03.
    * cornerSmooth: must be an integer between 80 and 2000. The default value is 1000. Default value is 0. 
    * xTilt: The value range is -0.5~0.5. Default value is 0. Default is 0. 
    * yTilt: -0.5~0.5. Default is 0.
    * overScanX: must be an integer between -125 and 125. The default value is 100.
    * overScanY: must be an integer between -125 and 125. The default value is 100.
    * dotMask: The value range is 0~0.3. The default value is 0.3.
    * sharper: The larger the value, the clearer the image. Must be an integer between 1 and 3. The default value is 1.
    * scanlineWeight: The value range is 0.1~0.5. The default value is 0.3.
    * lum: Used to boost the brightness. The default value is 0.
    * interlace: if or not to simulate interlacing. Boolean type. The default value is true.
* CRT_Hyllian: Provides sharp and clear output with a slight halo, similar to Sony's BVM series displays.
  * Output size: depends on the scale parameter
  * Parameter
    * scale: scale. An integer multiple scaling is recommended.
    * phosphor: Boolean type. Default value is true.
    * vScanlines: boolean type. The default value is false.
    * inputGamma: The range is 0~5. The default value is 2.5.
    * outputGamma: The range is 0~5. The default value is 2.2.
    * sharpness: must be an integer between 1 and 5. The default value is 1. Default value is 1.5. 
    * colorBoost: range 1~2. Default value is 1.5.
    * redBoost: range 1~2. Default value is 1. The default value is 1. 
    * greenBoost: The value range is 1~2. The default value is 1.The default value is 1. 
    * blueBoost: Takes a range of 1 to 2. The default value is 1.The default value is 0.5. 
    * scanlinesStrength: The value range is 0~1. The default value is 0.5.The default value is 0.86. 
    * beamMinWidth: The value range is 0~1. The default value is 0.86. 
    * beamMaxWidth: The value range is 0~1.
    * beamMaxWidth: The range is 0~1. The default value is 1. 
    * beamMaxWidth: The range is 0~1. The default value is 1.
    * crtAntiRinging: The range is 0~1. The default value is 0.8. 
    * crtAntiRinging: The range is 0~1. The default value is 0.8.
* CRT_Lottes: Provides various masks that can simulate Bloom and Halation effects. Similar to CGA arcade display.
  * Output size: depends on scale parameter.
  * Parameter
    * scale: scale parameter
    * hardScan: must be an integer between -20 and 0. Default value is -8.
    * hardPix: must be an integer between -20 and 0. The default value is -3.
    * warpX: range 0~0.125. Default value is 0.031.The default value is 0.041.
    * warpY: The range is 0~0.125.
    * maskDark: The range is 0~0.2. The default value is 0.5.
    * maskLight: 0~0.2. Default value is 1.5.
    * scaleInLinearGamma: Boolean type. Default value is true.
    * shadowMask: mask style. Must be an integer between 0 and 4. The default value is 3.default is 1. 
    * brightBoost: the range of 0~2. default is 1.
    * hardBloomPix: -2~-0.5. Default is -1.5.
    * hardBloomScan: -4~-1. Default value is -2. Default value is 0.15. 
    * bloomAmount: range 0~1. Default value is 0.15.
    * shape: range 0~10. default is 2.
* FineSharp: High quality sharpening effect, first scripted by AviSynth.
   * Output size: same as input
   * Parameters
     * sstr: sharpening intensity, must be greater than or equal to 0. Default value is 2. If this parameter is changed, change cstr as well, see remarks.
     * cstr: the intensity of equalization, must be greater than or equal to 0, default value is 0.9.
     * xstr: the intensity of the final sharpening step of the XSharpen style. Must be between 0 and 1, but preferably not more than 0.249. The default value is 0.19.
     * xrep: Used to fix artifacts produced by the final sharpening step. Must be greater than or equal to 0. Default value is 0.25.
   * Note: The correspondence between sstr and cstr (sstr->cstr): 0->0, 0.5->0.1, 1.0->0.6, 2.0->0.9, 2.5->1.00, 3.0->1.09, 3.5->1.15, 4.0->1.19, 8.0->1.249, 255.0->1.5

* FSR\_EASU and FSR\_EASU\_DX10: port of the scaling steps in [FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR).
    the DX10 suffix version works on DirectX feature level 10 cards, but
    is slightly slower.
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* FSR\_RCAS: Migration of sharpening steps in [FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR)
  * Output size: same as input
  * Parameters
    * sharpness: sharpening intensity. The value must be greater
            than 0. The larger the value, the sharper the image. The
            default value is 0.87.

* FSRCNNX: port of FSRCNNX\_x2\_8-0-4-1
  * Output size: twice the input

* FSRCNNX\_LineArt: Porting of FSRCNNX\_x2\_8-0-4-1\_LineArt
  * Output size: twice the input

* FXAA\_Medium, FXAA\_High and FXAA\_Ultra: Fast approximate anti-aliasing. The performance requirements increase in order
  * Output size: same as input
    
* GTU_v050: designed to simulate the blurring and blending effects of CRT screens instead of masks or curvature, supporting scan lines.
  * Output size: depends on the scale parameter
  * Parameter
    * scale: scale parameter
    * compositeConnection: boolean type, default value is false.
    * noScanlines: boolean type, default value is false.
    * signalResolution: integer, cannot be less than 16, default value is 256.
    * signalResolutionI: positive integer. Default value is 83.
    * signalResolutionQ: positive integer. Default value is 25.
    * tvVerticalResolution: integer, can't be less than 20, default is 250.
    * blackLevel: must be between -0.3~0.3. The default value is 0.07.
    * contrast: must be between 0~2. The default value is 1.

* Jinc: Scaling input using the Jinc algorithm
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter
    * windowSinc: the smaller the value, the sharper the image.
            Must be greater than 0, default value is 0.5
    * sinc: The larger the value, the sharper the image. Must be
            greater than 0, default value is 0.825

* Lanczos: scales the input using the Lanczos algorithm.
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter
    * ARStrength: Anti-ringing strength. The higher the value, the
            better the anti-ringing effect, but the more blurred
            the image. Must be between 0 and 1. The default value
            is 0.5.

* Linear: Bilinear interpolation
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* LumaSharpen: popular sharpening effect in reshade.
  * Output size: same as input
  * Parameters
    * sharpStrength: the sharpening strength. Must be greater than 0. Default value is 0.65.
    * sharpClamp: Anti-ringing strength. Must be between 0 and 1, the default value is 0.035.
    * pattern: filter type. Must be an integer from 0 to 3. There are 4 types of filters. The default value is 1.
    * offsetBias: the offset of the filter parameter. Must be greater than or equal to 0. The default value is 1.

* LumaSharpen: popular sharpening effect in reshade.
  * Output size: same as input
  * Parameters
    * sharpStrength: the sharpening strength. Must be greater than 0. Default value is 0.65.
    * sharpClamp: Anti-ringing strength. Must be between 0 and 1, the default value is 0.035.
    * pattern: filter type. Must be an integer from 0 to 3. There are 4 types of filters. The default value is 1.
    * offsetBias: the offset of the filter parameter. Must be greater than or equal to 0. The default value is 1.

* Nearest: Nearest neighbor interpolation
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* NIS: port of [NVIDIA Image Scaling](https://github.com/NVIDIAGameWorks/NVIDIAImageScaling).
  * Output size: depends on the scale parameter
  * Parameter
    * scale: scale parameter
    * sharpness: sharpening intensity. Must be between 0 and 1. Default value is 0.5.

* NVSharpen: port of NVSharpen released with NIS.
  * output size: same as input
  * Parameters
    * sharpness: sharpening intensity. Must be between 0 and 1, default value is 0.5.

* Pixellate: scales the input using the Pixellate algorithm. Suitable for scaling pixel pictures
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* RAVU\_Lite\_R3: porting of ravu-lite-r3
  * Output size: twice the input

* RAVU\_Zoom\_R3: port of ravu-zoom-r3
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* SharpBilinear: scales the input using the Sharp-Bilinear algorithm. Suitable for scaling pixel paintings
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* SMAA\_Low, SMAA\_Medium, SMAA\_High and SMAA\_Ultra: SMAA
    anti-aliasing algorithms. The requirements for performance increase
    in order
  * Output size: same as input

* SSimDownscaler: Perception-based image reduction algorithm that's
    sharper than Catrom
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

* xBRZ\_2x, xBRZ\_3x, xBRZ\_4x, xBRZ\_5x and xBRZ\_6x: Use the xBRZ
    algorithm to scale the input. Suitable for scaling pixel pictures
  * Output size: depends on the variant. Amplification to 2-6 times
        the input

* xBRZ\_Freescale and xBRZ\_Freescale\_Multipass: xBRZ algorithms
    supporting arbitrary scaling multiples
  * Output size: depends on scale parameter
  * Parameters
    * scale: scale parameter

##Example 
--------

1.  If the screen size is 2-4 times the source window, Anime4K can be
    applied twice, and the following fragment demonstrates
    this algorithm.

    ```json
    {
        "name": "Anime4k 4x",
        "effects": [
          {
            "effect": "Anime4K_Upscale_Denoise_L"
          },
          {
            "effect": "Bicubic",
            "scale": [ -0.5, -0.5 ]
          },
          {
            "effect": "Anime4K_Upscale_L"
          }
        ]
    }
    ```

    To improve performance, after the first application of Anime4K it is
    scaled to half the size of the maximum isometric scale that the
    screen can accommodate, so that after the second application of
    Anime4K it is displayed exactly full screen. To eliminate minor
    noise in the image, the first application of Anime4K is a
    noise-reduced version.

1.  Output the captured window to the center of the screen (surrounded
    by black borders)

    ```json
    {
        "name": "Source",
        "effects": [
          {
            "effect": "Nearest"
          }
        ]
    }
    ```

👉 [More examples](https://gist.github.com/hooke007/818ecc88f18e229bca743b7ae48947ad)
