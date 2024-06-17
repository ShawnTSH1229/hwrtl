# hwrtl
Hardware ray tracing library for GI Baker, HLOD Generation, PVS and Visibility Texture Generation


## GI Baking With Ray Guiding

### Usage

just copy and include "hwrtl_dx12.cpp", "hwrtl.h", "hwrtl_gi.cpp", "hwrtl_gi.h", "hwrtl_gi.hlsl" to your project.

### Implementation

Firstly, we pack the lightmaps of each mesh into a number of atlases and search for the best lightmap layout with the **smallest** total size. The packing algorithm uses a third-party library: **stb_pack**. Then, generate the **lightmap gbuffer** by GPU and start light map path tracing. For each texels in the light map gbuffer, we trace 512 rays from the world position recorded in the gbuffer and each tracing bounces 32 times. For each bounce, we perform a light sampling and material sampling and combine them by **multi-importance sampling** to reduce variance.

Furthermore, we have implemented part of the **ray-guiding algorithm**. First, we split the light map into **clusters** and each cluster shares the same luminance distribution, which can amplify the number of learning rays and reduce variance in the learned ray distribution. Then, map the ray sample direction of the first bounce into 2D, store the luminance at the corresponding position in the cluster and build the luminance distribution. After that, we build the luminance **CDF** in the compute shader by wave instruction. During the latter path tracing pass, we **adjust the sample direction and PDF** based on the ray guiding CDF.

We perform a simple **dilate pass** in order to solve the sampling bleed problem caused by bilinear sampling.

Unreal GPULM employs **Odin**(Open Image Denoise) to denoise the traced lightmap. We have implemented a custom denoising algorithm (**Non-local means filtering**)  to replace the Odin, since HWRTL design goal is a single file hardware raytracing library and we don't want to involve the thirdparty.

GI baking result:
<p align="left">
    <img src="/doc/result.png" width="60%" height="60%">
</p>

