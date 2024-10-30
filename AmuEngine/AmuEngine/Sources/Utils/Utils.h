#pragma once
#include "Size.h"
#include <string>
#include <vector>

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
	static std::string projectDirectory; 
	static std::string projectName;
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
}