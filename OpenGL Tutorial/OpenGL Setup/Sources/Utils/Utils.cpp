#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "../Camera/Camera.h"
#include <Input.h>

void AESleep(long long t)
{
    if (t <= 0)
        return;
    std::this_thread::sleep_for(std::chrono::seconds(t)); // 3ÃÊ Áö¿¬
}

float GetMouseCursorPositionX()
{
    int x, y;
    InputGetCursorPosition(&x, &y);
    x -= windowWidthHalf;
    return (float)x;
}

float GetMouseCursorPositionY()
{
    int x, y;
    InputGetCursorPosition(&x, &y);
    y -= windowHeightHalf;
    y = -y;
    return (float)y;
}
float GetCamPositionX()
{
    float x, y;
    Camera::GetInstance().GetPos(&x, &y);
    return x;
}

float GetCamPositionY()
{
    float x, y;
    Camera::GetInstance().GetPos(&x, &y);
    return y;
}

int PosToMapX(float x)
{
    return (int)(x + (windowWidth / 2)) / (windowWidth / width);
}

int PosToMapY(float y)
{
    return (int)(y + (windowHeight / 2)) / (windowHeight / height);
}

float MapToPosX(float ind)
{
    //return (windowWidth / width) * ind - (windowWidth / 2) + ((windowWidth / width) / 2);
    return ind * width;
}

float MapToPosY(float ind)
{
    //return -((windowHeight / height) * ind - (windowHeight / 2) + ((windowHeight / height) / 2));
    return -ind * height;
}

float GetSqDistance(float ax, float ay, float bx, float by)
{
    return ((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by));
}