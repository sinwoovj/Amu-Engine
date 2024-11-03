#include "FrameCounter.h"

void FrameCounter::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> frameDuration = currentTime - lastTime;

    deltaTime = frameDuration.count();   // �����Ӵ� �ɸ� �ð� (�� ����)
    frameCount++;

    // 1�ʸ��� FPS�� ����
    if (frameDuration.count() >= 1.0f) {
        fps = frameCount / frameDuration.count();
        frameCount = 0;
        lastTime = currentTime;
    }
}
