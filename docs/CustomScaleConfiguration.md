This document guides you on how to define your own scaling mode. // Translated from [自定义缩放配置.md](https://github.com/Z-Dante/Magpie/blob/master/docs/%E8%87%AA%E5%AE%9A%E4%B9%89%E7%BC%A9%E6%94%BE%E9%85%8D%E7%BD%AE.md) using [DeepL](https://www.deepl.com/translator)

When Magpie starts, it will search for the configuration file  **"ScaleModels.json"** 
in the root directory of where the program is located, and if it is not found, it will
be automatically generated using the program's built-in default
parameters.\
The full contents of the original configuration file can be [found
here](https://github.com/Z-Dante/Magpie/blob/master/Magpie/Resources/BuiltInScaleModels.json),
and the following is an example of the syntax format.
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
"scaling mode". A scaling mode is composed of a series of stacked effects that Magpie
applies one by one as it scales. *The configuration file supports json
comments, including line comments* `// `*and block comments* `/**/`*.*

Magpie has a large number of effects built in for use in combinations,
most of them provide various parameters options to customize its behavior. All
effects are stored in the "effects" folder, and if you know HLSL you can
easily add any effect you want, see [Custom
Effects](https://github.com/Blinue/Magpie/wiki/%E8%87%AA%E5%AE%9A%E4%B9%89%E6%95%88%E6%9E%9C%EF%BC%88MagpieFX%EF%BC%89).

Many effects support a **scale parameter**, whose value must be an array
with two elements. When the values are positive, they indicate the scale of
the length and height; when they are negative, they indicate the maximum
equivalent scale relative to what the screen can hold; when they are 0,
they indicate scaling to fill the screen (the screen may be stretched).
The default value for all scale parameters is \[1, 1\], which is the same
as the input size. You can see their application in the
[example.](#example)

Introduction of built-in effects 
---------------------------------

-   ACNet: port of [ACNetGLSL.](https://github.com/TianZerL/ACNetGLSL)
    Suitable for scaling of anime style images with strong noise
    reduction effect
    -   Output size: twice the input
 
-   AdaptiveSharpen: Adaptive sharpening algorithm. This algorithm
    focuses on sharpening the blurred edges in the image, so there is
    less noise, ringing and streaking than the usual
    sharpening algorithm.
    -   Output size: same as input
    -   Parameters
        -   curveHeight: sharpening intensity. Must be greater than
            zero, usually between 0.3 and 2.0. The default value is 1.0.
            
-   Anime4K\_3D\_AA\_Upscale\_US and Anime4K\_3D\_Upscale\_US: 3D game
    screen scaling algorithm provided by Anime4K. AA variants have
    anti-aliasing capabilities.
    -   Output size: twice the input

-   Anime4K\_Denoise\_Bilateral\_Mean,
    Anime4K\_Denoise\_Bilateral\_Median and
    Anime4K\_Denoise\_Bilateral\_Mode: noise reduction algorithms
    provided by Anime4K, using the mean, median and plural, respectively
    -   Output size: same as input
    -   Parameters
        -   intensitySigma: Noise reduction intensity. Must be greater
            than zero. The default value is 0.1.

-   Anime4K\_Restore\_M, Anime4K\_Restore\_L, and Anime4K\_Restore\_VL:
    algorithms provided by Anime4K for restoring anime lines, with
    sequentially higher performance requirements
    -   Output size: same as input
-   Anime4K\_Thin\_HQ: Algorithm provided by Anime4K to refine the lines
    of anime images
    -   Output size: same as input
    -   Parameters
        -   strength: the strength of each iteration, which must be
            greater than zero. The default value is 0.6.
        -   iterations: number of iterations, must be an integer greater
            than zero. The default value is 1. Decreasing the strength
            and increasing iterations will improve the picture quality,
            but will decrease the speed.

-   Anime4K\_Upscale\_S, Anime4K\_Upscale\_L,
    Anime4K\_Upscale\_Denoise\_S, Anime4K\_Upscale\_Denoise\_L and
    Anime4K\_Upscale\_GAN\_x2\_S: Animation-style image scaling
    algorithms provided by Anime4K. The Denoise variant includes noise
    reduction, the GAN variant is in the experimental stage and can
    retain more details
    -   Output size: twice the input

-   Anime4K\_Upscale\_S\_Lite: Lighter version of Anime4K\_Upscale\_S.
    Faster, but may have quality loss. Suitable for users with
    under-performing graphics cards.
    -   Output size: twice the input

-   Bicubic and Bicubic\_Lite: bicubic (bi-cubic)
    interpolation algorithm. lite variants are faster but may have
    quality loss for users with insufficient graphics card performance
    -   Output size: depends on the scale parameter Best when used
        for scaling.
    -   Parameters
        -   scale: scale, the value must be an array with two elements.
        -   paramB: filter parameter B, must be between 0 and 1. The
            default value is 0.333333. Too large a value will blur
        -   paramC: filter parameter C, must be between 0 and 1. The
            default value is 0.333333. Too large a value will
            generate ringing. Different variants of the algorithm can be
            implemented by freely combining different BC values, for
            example: Mitchell (B=C≈0.333333), Catmull-Rom (B=0 C=0.5),
            bicubic Photoshop (B=0 C=0.75), Spline ( B=1 C=0)

-   CAS: A port of
    [FidelityFX-CAS.](https://github.com/GPUOpen-Effects/FidelityFX-CAS)
    Lightweight sharpening effects
    -   Output size: same as input
    -   Parameters
        -   sharpness: must be between 0 and 1. The default value
            is 0.4.

-   FSR\_EASU and FSR\_EASU\_DX10: port of the scaling steps in
    [FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR).
    the DX10 suffix version works on DirectX feature level 10 cards, but
    is slightly slower.
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scale parameter

-   FSR\_RCAS: Migration of sharpening steps in
    [FidelityFX-FSR](https://github.com/GPUOpen-Effects/FidelityFX-FSR)
    -   Output size: same as input
    -   Parameters
        -   sharpness: sharpening intensity. The value must be greater
            than 0. The larger the value, the sharper the image. The
            default value is 0.87.

-   FSRCNNX: port of FSRCNNX\_x2\_8-0-4-1
    -   Output size: twice the input

-   FSRCNNX\_LineArt: Porting of FSRCNNX\_x2\_8-0-4-1\_LineArt
    -   Output size: twice the input

-   FXAA\_Medium, FXAA\_High and FXAA\_Ultra: Fast
    approximate anti-aliasing. The performance requirements increase in
    order
    -   Output size: same as input

-   Jinc: Scaling input using the Jinc algorithm
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scale parameter
        -   windowSinc: the smaller the value, the sharper the image.
            Must be greater than 0, default value is 0.5
        -   sinc: The larger the value, the sharper the image. Must be
            greater than 0, default value is 0.825

-   Lanczos: scales the input using the Lanczos algorithm.
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling
        -   ARStrength: Anti-ringing strength. The higher the value, the
            better the anti-ringing effect, but the more blurred
            the image. Must be between 0 and 1. The default value
            is 0.5.

-   Linear: Bilinear interpolation
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   Nearest: Nearest neighbor interpolation
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   Pixellate: scales the input using the Pixellate algorithm. Suitable
    for scaling pixel pictures
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   RAVU\_Lite\_R3: porting of ravu-lite-r3
    -   Output size: twice the input

-   RAVU\_Zoom\_R3: port of ravu-zoom-r3
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   SharpBilinear: scales the input using the Sharp-Bilinear algorithm.
    Suitable for scaling pixel paintings
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   SMAA\_Low, SMAA\_Medium, SMAA\_High and SMAA\_Ultra: SMAA
    anti-aliasing algorithms. The requirements for performance increase
    in order
    -   Output size: same as input

-   SSimDownscaler: Perception-based image reduction algorithm that's
    sharper than Catrom
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

-   xBRZ\_2x, xBRZ\_3x, xBRZ\_4x, xBRZ\_5x and xBRZ\_6x: Use the xBRZ
    algorithm to scale the input. Suitable for scaling pixel pictures
    -   Output size: depends on the variant. Amplification to 2-6 times
        the input

-   xBRZ\_Freescale and xBRZ\_Freescale\_Multipass: xBRZ algorithms
    supporting arbitrary scaling multiples
    -   Output size: depends on scale parameter
    -   Parameters
        -   scale: scaling

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
