#include "MainEditor.h"
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
            if (ImGui::MenuItem("Open File", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save File", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Load File", "Ctrl+L")) {}

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            if (ImGui::MenuItem("Quit", "Ctrl+Q")) { glfwSetWindowShouldClose(glfwGetCurrentContext(), true); }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Level"))
        {
            if (ImGui::MenuItem("New Level", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete Level", "Ctrl+D")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save Level", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Load Level", "Ctrl+L")) {}

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Object"))
        {
            if (ImGui::MenuItem("New Object", "Ctrl+N")) { /* Do stuff */ }
            if (ImGui::MenuItem("Delete Object", "Ctrl+D")) { /* Do stuff */ }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Show Levels", "Ctrl+L", &editor_data.ShowAllLevels))
            {

            }
            
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

void editor::MainEditor::ShowAllObject(bool* p_open)
{
    if (!ImGui::Begin("Objects", p_open))
    {
        ImGui::End();
    }
    else
    {
        ImGui::Text("Objects");
        ImGui::End();
    }
}

void editor::MainEditor::ShowAllLevel(bool* p_open)
{
    if (!ImGui::Begin("Levels", p_open))
    {
        ImGui::End();
    }
    else
    {
        ImGui::Text("Levels");
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

}

void editor::MainEditor::MainEditorUpdate()
{
    //Top Bar
    TopBar();
    // https://stackoverflow.com/questions/66955023/closing-an-imgui-window-this-seems-like-it-should-be-easy-how-does-one-do-it
    if (editor_data.ShowAllLevels) { ShowAllLevel(&editor_data.ShowAllLevels); }
    if (editor_data.ShowAllObects) { ShowAllObject(&editor_data.ShowAllObects); }
    
}

void editor::MainEditor::MainEditorExit()
{

}
