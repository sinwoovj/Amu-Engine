#include "MainEditor.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../Components/Components.h"
#include <vector>
#include <string>

editor::MainEditor::EDITOR_DATA editor::MainEditor::editor_data;

void editor::MainEditor::TopBar()
{

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("File Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("File Load", "Ctrl+L")) {}

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Level"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete", "Ctrl+D")) { /* Do stuff */ }
            if (ImGui::MenuItem("Level Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Level Load", "Ctrl+L")) {}

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Object"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete", "Ctrl+D")) { /* Do stuff */ }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Levels", "Ctrl+N", editor_data.ShowAllLevels))
            {

            }
            
            if (ImGui::MenuItem("Objects", "Ctrl+D", editor_data.ShowAllObects)) {

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

void editor::MainEditor::ShowAllObject()
{
    ImGui::Begin("Objects");

    ImGui::Text("Object");
    


    ImGui::SameLine();

    ImGui::End();
}

void editor::MainEditor::ShowAllLevel()
{
    ImGui::Begin("Levels");

    ImGui::Text("Level");

    ImGui::SameLine();

    ImGui::End();
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

}

void editor::MainEditor::MainEditorUpdate()
{
    //Top Bar
    TopBar();
    ShowAllObject();
    ShowAllLevel();
}

void editor::MainEditor::MainEditorExit()
{

}
