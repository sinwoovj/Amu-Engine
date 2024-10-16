#include "MainEditor.h"
#include "../Components/Components.h"
#include "../Level/LevelManager.h"
#include "../Serializer/Serializer.h"
#include "../GSM/GameStateManager.h"
#include "../Level/NormalLevel.h"
#include <vector>
#include <string>

editor::MainEditor::EDITOR_DATA editor::MainEditor::editor_data;

editor::MainEditor::~MainEditor()
{
    ImGui::DestroyContext();
}

void editor::MainEditor::PopUp()
{
    // PopUp

    // 새 오브젝트 생성 팝업 처리
    if (editor_data.showNewObjectPopup)
    {
        ImGui::OpenPopup("     Load Level Popup     ");  // 팝업 열기
        editor_data.showNewObjectPopup = false;  // 플래그 리셋
    }
    if (ImGui::BeginPopupModal("     Load Level Popup     ", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("     Save this level?     ");
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("Yes"))
        {
            Serializer::GetInstance().SaveLevel(editor_data.currLevelName);
            GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(editor_data.selectLevelName));
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("No"))
        {
            GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(editor_data.selectLevelName));
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //오브젝트 추가 팝업
    if (editor_data.showAddObjectPopup)
    {
        ImGui::OpenPopup("##Add Object##"); // 팝업 열기
        editor_data.showAddObjectPopup = false; // 플래그 리셋
    }

    if (ImGui::BeginPopup("##Add Object##"))
    {
        if (ImGui::InputText("Object Name", &editor_data.addObjName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            GameObjectManager::GetInstance().AddObject(editor_data.addObjName);
            if (GameObjectManager::GetInstance().GetObj(editor_data.addObjName) == nullptr)
                std::cout << "실패" << std::endl;
            else
                std::cout << "성공" << std::endl;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //오브젝트 우클릭 팝업
    if (editor_data.showObjectListRightClickPopup)
    {
        ImGui::OpenPopup("##Object List Right Click##"); // 팝업 열기
        editor_data.showObjectListRightClickPopup = false;
    }

    if (ImGui::BeginPopup("##Object List Right Click##"))
    {
        if (ImGui::MenuItem("Delete Object", NULL))
        {
            GameObjectManager::GetInstance().RemoveObject(editor_data.selectObjectName);
            if (GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName) != nullptr)
                std::cout << "실패" << std::endl;
            else
                std::cout << "성공" << std::endl;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void editor::MainEditor::TopBar()
{
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) != nullptr) // 가장 처음 로드할 때
    {
        editor_data.currLevelName = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
    }

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Quit", "Ctrl+Q")) { glfwSetWindowShouldClose(glfwGetCurrentContext(), true); }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Level"))
        {
            ImGui::SeparatorText("Level List");
            LevelManager::GetInstance().LoadLevels();
            
            for (auto& lvl : LevelManager::GetInstance().GetLevels())
            {
                if (lvl == "")
                    continue;
                if (ImGui::BeginMenu(lvl.c_str(), lvl != editor_data.currLevelName))
                {
                    if (ImGui::MenuItem("Delete Level", "Ctrl+D")) { 
                        if (LevelManager::GetInstance().DeleteLevel(lvl)) //Delete
                        {
                            // 성공
                            std::cout << "성공" << std::endl;
                        }
                        else
                        {
                            // 실패
                            std::cout << "실패" << std::endl;
                        }
                    }
                    if (ImGui::MenuItem("Load Level", "Ctrl+L")) { 
                        if (LevelManager::GetInstance().LoadLevel(lvl)) //Load
                        {
                            // 성공
                            editor_data.selectLevelName = lvl;
                            std::cout << "성공" << std::endl;
                        }
                        else
                        {
                            // 실패
                            std::cout << "실패" << std::endl;
                        }
                    }
                    ImGui::EndMenu();
                }
            }

            ImGui::SeparatorText("Level Option");

            if (ImGui::MenuItem("Save Current Level", "Ctrl+S")) {
                if (LevelManager::GetInstance().SaveLevel(editor_data.currLevelName))
                {
                    // 성공
                    std::cout << "성공" << std::endl;
                }
                else
                {
                    // 실패
                    std::cout << "실패" << std::endl;
                }
            }
            if (ImGui::BeginMenu("Add Level")) {
                if (ImGui::InputText("Level Name", &editor_data.addLvlName, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    if (LevelManager::GetInstance().AddLevel(editor_data.addLvlName))
                    {
                        // 성공
                        std::cout << "성공" << std::endl;
                    }
                    else
                    {
                        // 실패
                        std::cout << "실패" << std::endl;
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Show Objects", "Ctrl+O", &editor_data.showAllObjects)) {

            }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
    };

    PopUp();

    // End Main Menu Bar
    ImGui::EndMainMenuBar();
}

void editor::MainEditor::ShowLevelObject(bool* p_open)
{
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr)
    {
        if (ImGui::Begin("Create Any Level!"))
        {
            ImGui::SeparatorText("Object List");
            ImGui::SeparatorText("Object Option");
        }
        ImGui::End();
    }
    else
    {
        if (ImGui::Begin(dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName().c_str(), p_open))
        {
            ImGui::SeparatorText("Object List");
            for (auto& obj : GameObjectManager::GetInstance().GetAllObjects())
            {
                if (ImGui::TreeNode(obj.first.c_str()))
                {
                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                    {
                        editor_data.selectObjectName = obj.first;
                        editor_data.showObjectListRightClickPopup = true;
                    }
                    for (auto& comp : obj.second->GetComponents())
                    {
                        if (ImGui::TreeNode(comp.first.c_str()))
                        {
                            comp.second->Edit();
                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }
            }

            ImGui::SeparatorText("Object Option");
            ImGui::Columns(2, NULL, false);
            if (ImGui::Button("Add Object"))
            {
                editor_data.showAddObjectPopup = true;
            }

            ImGui::NextColumn();
            if (ImGui::Button("Delete All Object"))
            {
                GameObjectManager::GetInstance().RemoveAllObject();
                if (!GameObjectManager::GetInstance().GetAllObjects().empty())
                    std::cout << "실패" << std::endl;
                else
                    std::cout << "성공" << std::endl;
            }
            ImGui::End();
        }
    }
}

void editor::MainEditor::SelectedObjectWindow()
{
    //ImGui::Begin
}

void editor::MainEditor::ShowMenuWindow()
{

}

void editor::MainEditor::MainEditorInit(GLFWwindow* mainWindow)
{
    // Set Korean Font
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("./Sources/Assets/Fonts/NeoDunggeunmoPro-Regular.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
}

void editor::MainEditor::MainEditorUpdate()
{
    //Top Bar
    TopBar();
    // https://stackoverflow.com/questions/66955023/closing-an-imgui-window-this-seems-like-it-should-be-easy-how-does-one-do-it
    if (editor_data.showAllObjects) { ShowLevelObject(&editor_data.showAllObjects); }
    
}

void editor::MainEditor::MainEditorExit()
{

}
