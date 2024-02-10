﻿#include "RenderingKernelsLauncher.cuh"

#include "RenderingData.cuh"
#include "RenderingKernels.cuh"

void _RenderingKernelsLauncher::drawImage(
    GpuSettings const& gpuSettings,
    float2 rectUpperLeft,
    float2 rectLowerRight,
    int2 imageSize,
    float zoom,
    SimulationData data,
    RenderingData renderingData)
{
    uint64_t* targetImage = renderingData.imageData;

    KERNEL_CALL(cudaDrawBackground, targetImage, imageSize, data.worldSize, zoom, rectUpperLeft, rectLowerRight);
    KERNEL_CALL(cudaDrawCells, data.timestep, data.worldSize, rectUpperLeft, rectLowerRight, data.objects.cellPointers, targetImage, imageSize, zoom);
    KERNEL_CALL(cudaDrawParticles, data.worldSize, rectUpperLeft, rectLowerRight, data.objects.particlePointers, targetImage, imageSize, zoom);
    KERNEL_CALL_1_1(cudaDrawRadiationSources, targetImage, rectUpperLeft, data.worldSize, imageSize, zoom);
    KERNEL_CALL(cudaDrawRepetition, data.worldSize, imageSize, rectUpperLeft, rectLowerRight, targetImage, zoom);
}
