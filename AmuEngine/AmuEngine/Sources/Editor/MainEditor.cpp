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

void editor::MainEditor::TopBar()
{

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            //if (ImGui::MenuItem("Save All", "Ctrl+S")) { /* Do stuff */ }
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
                if (ImGui::BeginMenu(lvl.c_str()))
                {
                    if (ImGui::MenuItem("Delete Level", "Ctrl+D")) { 
                        if (LevelManager::GetInstance().DeleteLevel(lvl))
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
                        if (LevelManager::GetInstance().LoadLevel(lvl))
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
            }

            ImGui::SeparatorText("Level Option");

            if (ImGui::MenuItem("Save Current Level", "Ctrl+S")) {
                std::string currname = dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName();
                if (LevelManager::GetInstance().SaveLevel(currname))
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
                static std::string addLvlName = "";
                ImGui::InputText("Level Name", &addLvlName);
                if (ImGui::Button("Add"))
                {
                    if (LevelManager::GetInstance().AddLevel(addLvlName))
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
        //if (ImGui::BeginMenu("Object"))
        //{
        //    if (ImGui::MenuItem("New Object", "Ctrl+N")) { /* Do stuff */ }
        //    if (ImGui::MenuItem("Delete Object", "Ctrl+D")) { /* Do stuff */ }

        //    ImGui::Separator();
        //    if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
        //    ImGui::EndMenu();
        //}
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Show Objects", "Ctrl+O", &editor_data.ShowAllObects)) {

            }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
    };
    ImGui::EndMainMenuBar();

    /*
    Can Add Components
    Show Buttons with compnents options

    TODO : Move to factory
    */
    /*if (ImGui::TreeNode("Add Component"))
    {
        std::vector<std::string> comps = { TransformComp::TypeName, Sprite2D::GetName() };
        for (auto& compType : comps)
        {
            if
        }
    }*/
}

void editor::MainEditor::ShowLevelObject(bool* p_open)
{
    if (!ImGui::Begin((dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) == nullptr
        ? "Create Any Level!" : 
        dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName()).c_str(), p_open))
    {
        ImGui::End();
    }
    else
    {
        for (auto& obj : GameObjectManager::GetInstance().GetAllObjects())
        {
            if (ImGui::TreeNode(obj.second.c_str()))
            {
                for (auto& comp : obj.first->GetComponents())
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
        ImGui::End();
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
    if (editor_data.ShowAllObects) { ShowLevelObject(&editor_data.ShowAllObects); }
    
}

void editor::MainEditor::MainEditorExit()
{

}
