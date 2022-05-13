// CRT-Cathode
// 移植自 https://www.shadertoy.com/view/4lXcDH
// 要求整数倍缩放

//Cathode by nimitz (twitter: @stormoid)
//2017 nimitz All rights reserved

//Original taken from https://github.com/Blinue/MagpieToys

//!MAGPIE EFFECT
//!VERSION 2

//!TEXTURE
Texture2D INPUT;

//!SAMPLER
//!FILTER POINT
SamplerState sam;

//!PASS 1
//!STYLE PS
//!IN INPUT

//Phosphor decay
float decay(in float d) {
	return lerp(exp2(-d * d * 2.5 - .3), 0.05 / (d * d * d * 0.45 + 0.055), .65) * 0.99;
}

//Phosphor shape
float sqd(in float2 a, in float2 b) {
	a -= b;
	a *= float2(1.25, 1.8) * .905;
	float d = max(abs(a.x), abs(a.y));
	d = lerp(d, length(a * float2(1.05, 1.)) * 0.85, .3);
	return d;
}

float4 Pass1(float2 pos) {
	float2 inputSize = GetInputSize();
	float2 inputPt = GetInputPt();
	float2 outputSize = GetOutputSize();

	float2 p = pos * inputSize;

	float3 col = 0;
	p -= 0.25;
	float gl_FragCoordX = pos.x * outputSize.x;
	p.y += fmod(gl_FragCoordX, 2.) < 1. ? .03 : -0.03;
	p.y += fmod(gl_FragCoordX, 4.) < 2. ? .02 : -0.02;
    
	//5x5 kernel (this means a given fragment can be affected by a pixel 4 game pixels away)
	[unroll]
	for (int i = -2; i <= 2; i++) {
		[unroll]
		for (int j = -2; j <= 2; j++) {
			float2 tap = floor(p) + 0.5 + float2(i, j);
			float3 rez = INPUT.SampleLevel(sam, tap * float2(inputPt.x, inputPt.y), 0).rgb; //nearest neighbor
        
			//center points
			float rd = sqd(tap, p + float2(0.0, 0.2)); //distance to red dot
			const float xoff = .25;
			float gd = sqd(tap, p + float2(xoff, .0)); //distance to green dot
			float bd = sqd(tap, p + float2(-xoff, .0)); //distance to blue dot
		
			rez = pow(rez, 1.18) * 1.08;
			rez.r *= decay(rd);
			rez.g *= decay(gd);
			rez.b *= decay(bd);
		
			col += rez;
		}
	}

	return float4(col, 1.0);
}
