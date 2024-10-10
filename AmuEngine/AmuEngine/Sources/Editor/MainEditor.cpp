#include "MainEditor.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../Components/Components.h"
#include <vector>
#include <string>

void editor::MainEditor::TopBar()
{

    ImGui::BeginMainMenuBar();
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Load", "Ctrl+L")) {  }

            if (ImGui::MenuItem("---------")) { }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
                
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Level"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete", "Ctrl+D")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Object"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete", "Ctrl+D")) { /* Do stuff */ }
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
    ImGui::Begin("Object List");
    ImGui::End();

}

void editor::MainEditor::SelectedObjectWindow()
{
    //ImGui::Begin
}

void editor::MainEditor::MainEditorInit(GLFWwindow* mainWindow)
{

}

void editor::MainEditor::MainEditorUpdate()
{
    //Top Bar
    TopBar();

}

void editor::MainEditor::MainEditorExit()
{

}
