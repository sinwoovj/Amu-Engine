#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "../Camera/Camera.h"
#include <EasyOpengl.h>

void AESleep(long long t)
{
    if (t <= 0)
        return;
    std::this_thread::sleep_for(std::chrono::seconds(t)); // 3초 지연
}

float GetMouseCursorPositionX()
{
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    x -= windowWidthHalf;
    return (float)x;
}

float GetMouseCursorPositionY()
{
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
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


#include <windows.h>
#include <commdlg.h>  // For GetOpenFileName
#include <atlconv.h>

std::string Utility::OpenFileDialog()
{
    OPENFILENAME ofn;       // 공통 대화 상자 구조체
    wchar_t szFile[260];       // 파일 경로를 저장할 버퍼
    HWND hwnd = NULL;       // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)
    HANDLE hf = NULL;              // 파일 핸들

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return WstrTostr(ofn.lpstrFile);  // 선택된 파일 경로를 반환
    }

    return std::string();  // 아무것도 선택되지 않으면 빈 문자열 반환
}

std::string Utility::SaveFileDialog()
{
    OPENFILENAME ofn;       // 공통 대화 상자 구조체
    wchar_t szFile[260];    // 파일 경로를 저장할 버퍼 (wchar_t로 설정)
    HWND hwnd = NULL;       // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";  // 유니코드 문자열 사용
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetSaveFileNameW(&ofn) == TRUE)  // 유니코드 버전 사용
    {
        return WstrTostr(ofn.lpstrFile);  // 선택된 파일 경로를 반환
    }

    return std::string();  // 아무것도 선택되지 않으면 빈 문자열 반환
}

std::string Utility::WstrTostr(const std::wstring& in)
{
    USES_CONVERSION;
    return std::string(W2A(in.c_str()));
}