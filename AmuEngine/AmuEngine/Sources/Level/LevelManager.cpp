#include "LevelManager.h"
#include <iostream>
#include "../Serializer/Serializer.h"
#include "../GSM/GameStateManager.h"
#include <EasyImgui.h>
#include "NormalLevel.h"
#include <io.h>

extern bool showNewObjectPopup;

bool LevelManager::FindLevel(const std::string& str)
{
    for (auto& lvl : levels)
    {
        if (lvl == str)
        {
            return true;
        }
    }
    return false;
}

bool LevelManager::LoadLevels()
{
    levels.clear();
    std::string fileName = "*";
    std::string path = directory + fileName + filenameExtension; // ./Sources/Assets/Level/*.lvl
    struct _finddata_t fd;
    intptr_t handle;
    if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
        return false;
    do {
        std::string name = fd.name;
        name = name.substr(0, name.rfind(filenameExtension));
        levels.push_back(name);
        //std::cout << fd.name << std::endl;
    } while (_findnext(handle, &fd) == 0);
    _findclose(handle);

    return true;
}

bool LevelManager::SaveLevels()
{
    return false;
}

bool LevelManager::LoadLevel(const std::string& str)
{
    //　기존 레벨 파일에서 변경점이 있다면, 저장할 것인지 아닌지 팝업을 띄움
    if (!FindLevel(str))
        return false;
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr) // 가장 처음 로드할 때
    {
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(str));
        return true;
    }
    std::string currname = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
    if (Serializer::GetInstance().ExistChangePoint(currname))
    {
        showNewObjectPopup = true;
    }
    else
    {
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(str));
    }
    return true;
}
bool LevelManager::SaveLevel(const std::string& str)
{
    if (!FindLevel(str))
        return false;
    Serializer::GetInstance().SaveLevel(str);
    return true;
}

bool LevelManager::AddLevel(const std::string& str)
{
    return false;
}

bool LevelManager::DeleteLevel(const std::string& str)
{
    return false;
}

std::string LevelManager::GetDirectory()
{
    return directory;
}

std::string LevelManager::GetFilenameExtension()
{
    return filenameExtension;
}

void LevelManager::SetDirectory(const std::string& str)
{
    directory = str;
}

void LevelManager::SetFilenameExtension(const std::string& str)
{
    filenameExtension = str;
}
