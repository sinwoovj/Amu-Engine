#pragma once

#include <iostream>
#include <chrono>

class FrameCounter {
    int frameCount;
    float fps;
    float deltaTime; // 프레임당 걸린 시간 (초 단위)
    std::chrono::high_resolution_clock::time_point lastTime;
    std::chrono::high_resolution_clock::time_point previousTime;

    FrameCounter() : frameCount(0), fps(0), deltaTime(0.0f) {
        lastTime = std::chrono::high_resolution_clock::now();
    }
    ~FrameCounter() {};

    FrameCounter(const FrameCounter&) = delete;
    FrameCounter& operator =(const FrameCounter&) = delete;

    static FrameCounter* ptr;

public:
    static FrameCounter& GetInstance()
    {
        static FrameCounter instance;
        return instance;
    }

    void Update();

    float getFPS() const { 
        return fps; 
    }

    float getDeltaTime() const { 
        return deltaTime; 
    }

    void printFrameData() { std::cout << "FPS: " << GetInstance().getFPS() << " | Frame Time: " << GetInstance().getDeltaTime() << " seconds\n"; }
};