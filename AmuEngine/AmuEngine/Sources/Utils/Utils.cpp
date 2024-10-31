#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "../Camera/Camera.h"
#include <EasyOpengl.h>



std::string Utility::projectDirectory;
std::string Utility::projectName;

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
#include <string>
#include <filesystem>
#include <codecvt>


void Utility::InitUtility()
{
    Utility::projectDirectory = GetCurrentPath();
}

//result << 절대경로
std::string Utility::OpenFileDialog() 
{
    OPENFILENAME ofn;       // 공통 대화 상자 구조체
    wchar_t szFile[260];       // 파일 경로를 저장할 버퍼
    HWND hwnd = NULL;       // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All\0*.*\0Image\0*.PNG\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        std::string res = WstrTostr(ofn.lpstrFile);
        //res = AbsToRelPath(projectDirectory, res);

        return res;
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
        std::string res = WstrTostr(ofn.lpstrFile);
        return res;  // 선택된 파일 경로를 반환
    }

    return std::string();  // 아무것도 선택되지 않으면 빈 문자열 반환
}

std::string Utility::GetCurrentPath()
{
    // 충분한 크기의 버퍼를 할당합니다.
    char buffer[MAX_PATH];

    // 현재 작업 디렉토리를 가져옵니다.
    if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
        return std::string(buffer); // std::string으로 변환하여 반환
    }
    else {
        return ""; // 오류가 발생한 경우 빈 문자열 반환
    }
}


std::string Utility::WstrTostr(const std::wstring& in)
{
    /*std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(in);*/
    /*setlocale(LC_ALL, "");

    wchar_t* org = in;
    char buffer[300] = "";
    char* ptr = buffer;

    while (*org) {
        int sz = wctomb(ptr, *org);
        org++; ptr += sz;
    }
    std::string result(buffer);
    return result;*/
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, in.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string result(bufferSize, 0);
    WideCharToMultiByte(CP_UTF8, 0, in.c_str(), -1, &result[0], bufferSize, nullptr, nullptr);
    if (!result.back())
        result.pop_back();
    return result;
}

std::vector<std::string> Utility::splitPath(const std::string& path)
{
    std::vector<std::string> parts;
    std::string current;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '\\' || path[i] == '/') {
            if (!current.empty()) {
                parts.push_back(current);
                current.clear();
            }
        }
        else {
            current += path[i];
        }
    }
    if (!current.empty()) {
        parts.push_back(current);
    }
    return parts;
}

std::string Utility::AbsToRelPath(const std::string& base, const std::string& target)
{
    std::vector<std::string> baseParts = splitPath(base);
    std::vector<std::string> targetParts = splitPath(target);

    size_t commonIndex = 0;
    while (commonIndex < baseParts.size() && commonIndex < targetParts.size() &&
        baseParts[commonIndex] == targetParts[commonIndex]) {
        ++commonIndex;
    }

    std::string result;
    for (size_t i = commonIndex; i < baseParts.size(); ++i) {
        result += "../";
    }
    for (size_t i = commonIndex; i < targetParts.size(); ++i) {
        result += targetParts[i];
        if (i < targetParts.size() - 1) {
            result += "/";
        }
    }

    return "./" + result;
}

bool Utility::isMultibyte(std::string str)
{
    // 로케일 설정 (시스템 기본 로케일을 사용)
    setlocale(LC_ALL, "");
    
    // 멀티바이트인지 아닌지 확인
    return mblen(str.c_str(), MB_CUR_MAX) > 1;
}

