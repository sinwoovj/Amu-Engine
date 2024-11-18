#pragma once
#include "Size.h"
#include <string>
#include <vector>
#include <EasyOpengl.h>
#include <map>

void AESleep(long long t);
float GetMouseCursorPositionX();
float GetMouseCursorPositionY();
float GetCamPositionX();
float GetCamPositionY();
int PosToMapX(float x);
int PosToMapY(float y);
float MapToPosX(float ind);
float MapToPosY(float ind);
float GetSqDistance(float ax, float ay, float bx, float by);

namespace Utility {
	extern std::string projectDirectory;
	extern std::string projectName;
	enum FileDialogFilter {
		Image,
		Text,
		Video,
		Texture,
		Code
	};
	void InitUtility();
	std::string OpenFileDialog();
	std::string SaveFileDialog();
	std::string GetCurrentPath();
	std::string WstrTostr(const std::wstring& in);
	std::vector<std::string> splitPath(const std::string& path);
	std::string AbsToRelPath(const std::string& base, const std::string& target);

	glm::vec2 GetCurrentWindowSize();
	bool isMultibyte(std::string str);

    // GLFW Ű �� ����
	extern std::vector<int> keyMap;
	extern const char* keyTypes[120];
    // Ű �̸����� ���� ��ȯ�ϴ� �Լ�
	int getKeyValue(int index);
	int getKeyIndex(int value);
}