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
    // str에 해당하는 레벨이 있는지 확인
    if (std::find(levels.begin(), levels.end(), str) != levels.end())
    {
        // 중복되는 이름이 있다는 팝업을 띄움
        editor::MainEditor::editor_data.showAlreadyHaveSameNameLevelPopup = true;
        return false;
    }

    // lvl 디렉터리에 str에 해당하는 패스로 파일을 생성함, 해당 패스에 default.lvl를 저장한다.
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
    // str에 해당하는 레벨이 있는지 확인
    if (std::find(levels.begin(), levels.end(), str) == levels.end())
        return false;

    std::string currLvl;
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr)
        currLvl = "";
    else
        currLvl = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
    // 만약 지우려는 레벨이 현재 레벨이라면 지우고 현재 레벨 ""으로 설정
    if (str == currLvl)
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(""));

    // levels에서 str에 해당하는 lvl 지우기
    levels.erase(std::remove(levels.begin(), levels.end(), str), levels.end());

    // 파일 삭제
    std::string path = directory + str + filenameExtension; // ./Sources/Assets/Level/{str}.lvl
    // _unlink()는 파일을 삭제할 때 사용 -- return value (0 = complete, -1 = fail)
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
