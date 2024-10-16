#include "LevelManager.h"
#include <iostream>
#include <fstream>
#include "../Serializer/Serializer.h"
#include "../GSM/GameStateManager.h"
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>
#include "NormalLevel.h"
#include <io.h>
#include "../Editor/MainEditor.h"
#include "json.hpp"

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

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
    //������ ���� ���Ͽ��� �������� �ִٸ�, ������ ������ �ƴ��� �˾��� ���
    if (!FindLevel(str))
        return false;
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr) // ���� ó�� �ε��� ��
    {
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(str));
        return true;
    }
    std::string currname = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
    if (Serializer::GetInstance().ExistChangePoint(currname))
    {
        editor::MainEditor::editor_data.showNewObjectPopup = true;
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

bool LevelManager::UndoLevel(const std::string& str)
{
    if (!FindLevel(str))
        return false;
    Serializer::GetInstance().LoadLevel(str);
    return true;
}

bool LevelManager::AddLevel(const std::string& str)
{
    // str�� �ش��ϴ� ������ �ִ��� Ȯ��
    if (std::find(levels.begin(), levels.end(), str) != levels.end())
    {
        // �ߺ��Ǵ� �̸��� �ִٴ� �˾��� ���
        editor::MainEditor::editor_data.showAlreadyHaveSameNameLevelPopup = true;
        return false;
    }

    // lvl ���͸��� str�� �ش��ϴ� �н��� ������ ������, �ش� �н��� default.lvl�� �����Ѵ�.
    std::string defaultLvlFilename = "./Sources/default.lvl";
    
    // Open file
    std::fstream defaultLvlFile;
    defaultLvlFile.open(defaultLvlFilename, std::fstream::in);

    // Check the file is valid
    if (!defaultLvlFile.is_open())
         throw std::invalid_argument("defaultLvlFile Invalid filename " + defaultLvlFilename);

    json allData;
    defaultLvlFile >> allData;	// the json has all the file data

    std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();

    // Open file
    std::ofstream file;
    file.open(filename, std::fstream::out);	// Open as write mode. Create it if it does not exist!

    if (!file.is_open())
        return false;
    //throw std::invalid_argument("Serializer::SaveLevel file write error " + str);

    file << std::setw(2) << allData;	// Separates in lines and each section

    file.close();
    return true;
}

bool LevelManager::DeleteLevel(const std::string& str)
{
    // str�� �ش��ϴ� ������ �ִ��� Ȯ��
    if (std::find(levels.begin(), levels.end(), str) == levels.end())
        return false;

    std::string currLvl;
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr)
        currLvl = "";
    else
        currLvl = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
    // ���� ������� ������ ���� �����̶�� ����� ���� ���� ""���� ����
    if (str == currLvl)
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(""));

    // levels���� str�� �ش��ϴ� lvl �����
    levels.erase(std::remove(levels.begin(), levels.end(), str), levels.end());

    // ���� ����
    std::string path = directory + str + filenameExtension; // ./Sources/Assets/Level/{str}.lvl
    // _unlink()�� ������ ������ �� ��� -- return value (0 = complete, -1 = fail)
    if (_unlink(path.c_str()) == 0) {
        std::cout << path << " : File deleted successfully.\n";
    }
    else {
        std::perror("Error deleting file");
        return false;
    }

    return true;
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
