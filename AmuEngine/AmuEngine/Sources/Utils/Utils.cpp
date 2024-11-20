#include "Utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "../Camera/Camera.h"
#include <EasyOpengl.h>
#include <direct.h>
#include <algorithm> // std::find


std::string Utility::projectDirectory;
std::string Utility::projectName;

std::vector<int> Utility::keyMap
{
    32,39,44,45,46,47,48,49,50,51,
    52,53,54,55,56,57,59,61,65,66,
    67,68,69,70,71,72,73,74,75,76,
    77,78,79,80,81,82,83,84,85,86,
    87,88,89,90,91,92,93,96,161,162,
    256,257,258,259,260,261,262,263,264,265,
    266,267,268,269,280,281,282,283,284,290,
    291,292,293,294,295,296,297,298,299,300,
    301,302,303,304,305,306,307,308,309,310,
    311,312,313,314,320,321,322,323,324,325,
    326,327,328,329,330,331,332,333,334,335,
    336,340,341,342,343,344,345,346,347,348
};
const char* Utility::keyTypes[120]
{
    "KEY_SPACE",
    "KEY_APOSTROPHE",
    "KEY_COMMA",
    "KEY_MINUS",
    "KEY_PERIOD",
    "KEY_SLASH",
    "KEY_0",
    "KEY_1",
    "KEY_2",
    "KEY_3",
    "KEY_4",
    "KEY_5",
    "KEY_6",
    "KEY_7",
    "KEY_8",
    "KEY_9",
    "KEY_SEMICOLON",
    "KEY_EQUAL",
    "KEY_A",
    "KEY_B",
    "KEY_C",
    "KEY_D",
    "KEY_E",
    "KEY_F",
    "KEY_G",
    "KEY_H",
    "KEY_I",
    "KEY_J",
    "KEY_K",
    "KEY_L",
    "KEY_M",
    "KEY_N",
    "KEY_O",
    "KEY_P",
    "KEY_Q",
    "KEY_R",
    "KEY_S",
    "KEY_T",
    "KEY_U",
    "KEY_V",
    "KEY_W",
    "KEY_X",
    "KEY_Y",
    "KEY_Z",
    "KEY_LEFT_BRACKET",
    "KEY_BACKSLASH",
    "KEY_RIGHT_BRACKET",
    "KEY_GRAVE_ACCENT",
    "KEY_WORLD_1",
    "KEY_WORLD_2",
    "KEY_ESCAPE",
    "KEY_ENTER",
    "KEY_TAB",
    "KEY_BACKSPACE",
    "KEY_INSERT",
    "KEY_DELETE",
    "KEY_RIGHT",
    "KEY_LEFT",
    "KEY_DOWN",
    "KEY_UP",
    "KEY_PAGE_UP",
    "KEY_PAGE_DOWN",
    "KEY_HOME",
    "KEY_END",
    "KEY_CAPS_LOCK",
    "KEY_SCROLL_LOCK",
    "KEY_NUM_LOCK",
    "KEY_PRINT_SCREEN",
    "KEY_PAUSE",
    "KEY_F1",
    "KEY_F2",
    "KEY_F3",
    "KEY_F4",
    "KEY_F5",
    "KEY_F6",
    "KEY_F7",
    "KEY_F8",
    "KEY_F9",
    "KEY_F10",
    "KEY_F11",
    "KEY_F12",
    "KEY_F13",
    "KEY_F14",
    "KEY_F15",
    "KEY_F16",
    "KEY_F17",
    "KEY_F18",
    "KEY_F19",
    "KEY_F20",
    "KEY_F21",
    "KEY_F22",
    "KEY_F23",
    "KEY_F24",
    "KEY_F25",
    "KEY_KP_0",
    "KEY_KP_1",
    "KEY_KP_2",
    "KEY_KP_3",
    "KEY_KP_4",
    "KEY_KP_5",
    "KEY_KP_6",
    "KEY_KP_7",
    "KEY_KP_8",
    "KEY_KP_9",
    "KEY_KP_DECIMAL",
    "KEY_KP_DIVIDE",
    "KEY_KP_MULTIPLY",
    "KEY_KP_SUBTRACT",
    "KEY_KP_ADD",
    "KEY_KP_ENTER",
    "KEY_KP_EQUAL",
    "KEY_LEFT_SHIFT",
    "KEY_LEFT_CONTROL",
    "KEY_LEFT_ALT",
    "KEY_LEFT_SUPER",
    "KEY_RIGHT_SHIFT",
    "KEY_RIGHT_CONTROL",
    "KEY_RIGHT_ALT",
    "KEY_RIGHT_SUPER",
    "KEY_MENU"
};

void AESleep(long long t)
{
    if (t <= 0)
        return;
    std::this_thread::sleep_for(std::chrono::seconds(t)); // 3�� ����
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
    return (int)(x + ((int)Utility::GetCurrentWindowSize().x / static_cast<float>(2))) / (int)(Utility::GetCurrentWindowSize().x / width);
}

int PosToMapY(float y)
{
    return (int)(y + ((int)Utility::GetCurrentWindowSize().y / static_cast<float>(2))) / ((int)Utility::GetCurrentWindowSize().y / height);
}

float MapToPosX(float ind)
{
    return ind * width;
}

float MapToPosY(float ind)
{
    return -ind * height;
}

float GetSqDistance(float ax, float ay, float bx, float by)
{
    return ((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by));
}


#include <windows.h>
#include <string>
#include <codecvt>


void Utility::InitUtility()
{
    Utility::projectDirectory = GetCurrentPath();
}

//result << ������
std::string Utility::OpenFileDialog() 
{
    OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
    wchar_t szFile[260];       // ���� ��θ� ������ ����
    HWND hwnd = NULL;       // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)

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
        res = AbsToRelPath(projectDirectory, res);

        if (_chdir(projectDirectory.c_str()) == 0) { // ���� �� 0 ��ȯ
            std::cout << "�۾� ���丮�� ������Ʈ ���͸��� ����Ǿ����ϴ�.\n";
        }
        else {
            std::cerr << "���丮 ���濡 �����߽��ϴ�.\n";
        }
        return res;
    }

    return std::string();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}

std::string Utility::SaveFileDialog()
{
    OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
    wchar_t szFile[260];    // ���� ��θ� ������ ���� (wchar_t�� ����)
    HWND hwnd = NULL;       // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";  // �����ڵ� ���ڿ� ���
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


    if (GetSaveFileNameW(&ofn) == TRUE)  // �����ڵ� ���� ���
    {
        std::string res = WstrTostr(ofn.lpstrFile);
        res = AbsToRelPath(projectDirectory, res);
        return res;  // ���õ� ���� ��θ� ��ȯ
    }

    return std::string();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}

std::string Utility::GetCurrentPath()
{
    // ����� ũ���� ���۸� �Ҵ��մϴ�.
    char buffer[MAX_PATH];

    // ���� �۾� ���丮�� �����ɴϴ�.
    if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
        return std::string(buffer); // std::string���� ��ȯ�Ͽ� ��ȯ
    }
    else {
        return ""; // ������ �߻��� ��� �� ���ڿ� ��ȯ
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

bool Utility::GetStateWindowSize()
{
    if (GetCurrentWindowSize().x != 1600 || GetCurrentWindowSize().y != 900)
        return true;
    return false;
}

glm::vec<2, int> Utility::GetCurrentWindowSize()
{
    int x, y;
    glfwGetWindowSize(glfwGetCurrentContext(), &x, &y);
    return glm::vec<2, int>(x,y);
}

void Utility::SetCurrentWindowSize(glm::vec2 size)
{
    glfwSetWindowSize(glfwGetCurrentContext(), size.x, size.y);
}

bool Utility::isMultibyte(std::string str)
{
    // ������ ���� (�ý��� �⺻ �������� ���)
    setlocale(LC_ALL, "");
    
    // ��Ƽ����Ʈ���� �ƴ��� Ȯ��
    return mblen(str.c_str(), MB_CUR_MAX) > 1;
}

int Utility::getKeyValue(int index) {
    return keyMap.at(index);
}

int Utility::getKeyIndex(int value)
{
    return int(std::find(keyMap.begin(), keyMap.end(), value) - keyMap.begin());
}