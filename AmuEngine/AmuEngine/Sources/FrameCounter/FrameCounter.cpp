#include "FrameCounter.h"

#include <opengl.h>

void FrameCounter::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
    previousTime = currentTime;

    std::chrono::duration<float> frameDuration = currentTime - lastTime;
    frameCount++;

    // 1�ʸ��� FPS�� ����
    if (frameDuration.count() >= 1.0f) {
        fps = frameCount / frameDuration.count();
        frameCount = 0;
        lastTime = currentTime;
    }
}
