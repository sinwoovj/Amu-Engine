#include "FrameCounter.h"

void FrameCounter::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> frameDuration = currentTime - lastTime;

    deltaTime = frameDuration.count();   // 프레임당 걸린 시간 (초 단위)
    frameCount++;

    // 1초마다 FPS를 갱신
    if (frameDuration.count() >= 1.0f) {
        fps = frameCount / frameDuration.count();
        frameCount = 0;
        lastTime = currentTime;
    }
}
