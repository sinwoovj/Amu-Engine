#include "MainEditor.h"
#include "../Components/Components.h"
#include "../Level/LevelManager.h"
#include "../Serializer/Serializer.h"
#include "../GSM/GameStateManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GSM/GameStateManager.h"
#include "../Components/Components.h"
#include "../Level/NormalLevel.h"
#include <vector>
#include <string>

editor::MainEditor::EditorMode editor::MainEditor::editorMode = Edit;

editor::MainEditor::EDITOR_DATA editor::MainEditor::editor_data;

editor::MainEditor::~MainEditor()
{
}

void editor::MainEditor::PopUp()
{
    // PopUp

    // �� ������Ʈ ���� �˾� ó��
    if (editor_data.showNewObjectPopup)
    {
        ImGui::OpenPopup("     Load Level Popup     ");  // �˾� ����
        editor_data.showNewObjectPopup = false;  // �÷��� ����
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
            editorMode = Edit;
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
            editorMode = Edit;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //������Ʈ �߰� �˾�
    if (editor_data.showAddObjectPopup)
    {
        ImGui::OpenPopup("##Add Object##"); // �˾� ����
        editor_data.showAddObjectPopup = false; // �÷��� ����
    }

    if (ImGui::BeginPopup("##Add Object##"))
    {
        if (ImGui::InputText("Object Name", &editor_data.addObjName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if(!GameObjectManager::GetInstance().AddObject(editor_data.addObjName))
                editor_data.showAlreadyHaveSameNameObjectPopup = true;
            if (GameObjectManager::GetInstance().GetObj(editor_data.addObjName) == nullptr)
                std::cout << "����" << std::endl;
            else
                std::cout << "����" << std::endl;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //������Ʈ ��Ŭ�� �˾�
    if (editor_data.showObjectListRightClickPopup)
    {
        ImGui::OpenPopup("##Object List Right Click##"); // �˾� ����
        editor_data.showObjectListRightClickPopup = false;
    }

    if (ImGui::BeginPopup("##Object List Right Click##"))
    {
        if (ImGui::MenuItem("Delete Object", NULL))
        {
            GameObjectManager::GetInstance().RemoveObject(editor_data.selectObjectName);
            if (GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName) != nullptr)
                std::cout << "����" << std::endl;
            else
                std::cout << "����" << std::endl;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::BeginMenu("Add Component"))
        {
            GameObject* obj = GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName);
            for (auto& cName : compName)
            {
                if (ImGui::MenuItem(cName.c_str(), NULL, false, !obj->ExistComponent(cName) && !obj->ExistSingletonComponent(cName)))
                {
                    obj->AddComponent(cName);
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

    //���� �̸��� ������ ���� �� ���� �˾�
    if (editor_data.showAlreadyHaveSameNameLevelPopup)
    {
        ImGui::OpenPopup("     Warning : Delete Level     ");
        editor_data.showAlreadyHaveSameNameLevelPopup = false;
    }

    if (ImGui::BeginPopup("     Warning : Delete Level     "))
    {
        ImGui::Text("This level name is already exist.\n Please type another level name.");
        ImGui::Columns(1);
        if (ImGui::Button("Ok"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //���� �̸��� ������Ʈ�� ���� �� ���� �˾�
    if (editor_data.showAlreadyHaveSameNameObjectPopup)
    {
        ImGui::OpenPopup("     Warning : Delete Object     ");
        editor_data.showAlreadyHaveSameNameObjectPopup = false;
    }

    if (ImGui::BeginPopup("     Warning : Delete Object     "))
    {
        ImGui::Text("This Object name is already exist.\n Please type another Object name.");
        ImGui::Columns(1);
        if (ImGui::Button("Ok"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //Level �߰� �˾�
    if (editor_data.showAddLevelPopup)
    {
        ImGui::OpenPopup("##Add Level##");
        editor_data.showAddLevelPopup = false;
    }
    if (ImGui::BeginPopup("##Add Level##"))
    {
        if (ImGui::InputText("Level Name", &editor_data.addLvlName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if (LevelManager::GetInstance().AddLevel(editor_data.addLvlName))
            {
                // ����
                std::cout << "����" << std::endl;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //������Ʈ ��Ŭ�� �˾�
    if (editor_data.showCompListRightClickPopup)
    {
        ImGui::OpenPopup("##Delete Component##");
        editor_data.showCompListRightClickPopup = false;
    }
    if (ImGui::BeginPopup("##Delete Component##"))
    {
        if (ImGui::MenuItem("Delete Component"))
        {
            GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName)->RemoveComponent(editor_data.selectCompName);
            if (!GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName)->ExistComponent(editor_data.selectCompName))
            {
                // ����
                std::cout << "����" << std::endl;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //���̾� �߰� �˾�
    if (editor_data.showAddLayerPopup)
    {
        ImGui::OpenPopup("##Add Layer##");
        editor_data.showAddLayerPopup = false;
    }
    if (ImGui::BeginPopup("##Add Layer##"))
    {
        if (ImGui::InputText("Layer Name", &editor_data.addLayerName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if (GameObjectManager::GetInstance().AddObjectLayer(editor_data.addLayerName))
            {
                // ����
                std::cout << "����" << std::endl;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    //���̾� ���� �˾�
    if (editor_data.showRemoveLayerPopup)
    {
        ImGui::OpenPopup("##Remove Layer##");
        editor_data.showRemoveLayerPopup = false;
    }
    if (ImGui::BeginPopup("##Remove Layer##"))
    {
        auto layers = GameObjectManager::GetInstance().GetLayers();
        if (ImGui::BeginListBox("##Remove Layer##"))
        {
            for (int n = 0; n < (int)layers.size(); n++)
            {
                const bool is_selected = (editor_data.remove_layer_item_selected_idx == n);
                bool is_layer_default = false;
                for (auto& it : GameObjectManager::GetInstance().DefaultLayer)
                {
                    if (it == layers.at(n))
                        is_layer_default = true;
                }
                if (is_layer_default) continue;
                if (ImGui::Selectable(layers.at(n).c_str(), is_selected))
                {
                    editor_data.remove_layer_item_selected_idx = n;
                    if (GameObjectManager::GetInstance().RemoveObjectLayer(layers.at(n)))
                    {
                        // ����
                        std::cout << "����" << std::endl;
                    }
                    else
                    {
                        // ����
                        std::cout << "����" << std::endl;
                    }
                    ImGui::CloseCurrentPopup();
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::EndPopup();
    }
    //�±� �߰� �˾�
    if (editor_data.showAddTagPopup)
    {
        ImGui::OpenPopup("##Add Tag##");
        editor_data.showAddTagPopup = false;
    }
    if (ImGui::BeginPopup("##Add Tag##"))
    {
        if (ImGui::InputText("Tag Name", &editor_data.addTagName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            if (GameObjectManager::GetInstance().AddObjectTag(editor_data.addTagName))
            {
                // ����
                std::cout << "����" << std::endl;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    //�±� ���� �˾�
    if (editor_data.showRemoveTagPopup)
    {
        ImGui::OpenPopup("##Remove Tag##");
        editor_data.showRemoveTagPopup = false;
    }
    if (ImGui::BeginPopup("##Remove Tag##"))
    {
        auto tags = GameObjectManager::GetInstance().GetTags();

        if (ImGui::BeginListBox("##Remove Tag##"))
        {
            for (int n = 0; n < (int)tags.size(); n++)
            {
                const bool is_selected = (editor_data.remove_tag_item_selected_idx == n);
                bool is_tag_default = false;
                for (auto& it : GameObjectManager::GetInstance().DefaultTag)
                {
                    if (it == tags.at(n))
                        is_tag_default = true;
                }
                if (is_tag_default) continue;
                if (ImGui::Selectable(tags.at(n).c_str(), is_selected))
                {
                    editor_data.remove_tag_item_selected_idx = n;
                    if (GameObjectManager::GetInstance().RemoveObjectTag(tags.at(n)))
                    {
                        // ����
                        std::cout << "����" << std::endl;
                    }
                    else
                    {
                        // ����
                        std::cout << "����" << std::endl;
                    }
                    ImGui::CloseCurrentPopup();
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::EndPopup();
    }
}

void editor::MainEditor::TopBar()
{
    if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) != nullptr) // ���� ó�� �ε��� ��
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
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, editorMode == Play || editorMode == Pause);
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
                    if (ImGui::MenuItem("Load Level", "Ctrl+L")) {
                        if (LevelManager::GetInstance().LoadLevel(lvl)) //Load
                        {
                            // ����
                            editor_data.selectLevelName = lvl;
                            std::cout << "����" << std::endl;
                        }
                        else
                        {
                            // ����
                            std::cout << "����" << std::endl;
                        }
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem("Delete Level", "Ctrl+D")) { 
                        if (LevelManager::GetInstance().DeleteLevel(lvl)) //Delete
                        {
                            // ����
                            std::cout << "����" << std::endl;
                        }
                        else
                        {
                            // ����
                            std::cout << "����" << std::endl;
                        }
                    }
                    ImGui::EndMenu();
                }
            }

            ImGui::SeparatorText("Level Option");

            if (ImGui::MenuItem("Save Level", "Ctrl+S")) {
                if (LevelManager::GetInstance().SaveLevel(editor_data.currLevelName))
                {
                    // ����
                    std::cout << "����" << std::endl;
                }
                else
                {
                    // ����
                    std::cout << "����" << std::endl;
                }
            }
            if (ImGui::MenuItem("Undo Level", "Ctrl+U")) {
                if (LevelManager::GetInstance().UndoLevel(editor_data.currLevelName))
                {
                    // ����
                    std::cout << "����" << std::endl;
                }
                else
                {
                    // ����
                    std::cout << "����" << std::endl;
                }
            }
            if (ImGui::MenuItem("Add Level", "Ctrl+A")) {
                editor_data.showAddLevelPopup = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { 
                ImGui::CloseCurrentPopup(); 
            }
            ImGui::EndMenu();
        }
        ImGui::PopItemFlag();
        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Show Objects", "Ctrl+O", &editor_data.showAllObjects)) {

            }

            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Ctrl+W")) { ImGui::CloseCurrentPopup(); }
            ImGui::EndMenu();
        }

        // UV coordinates are often (0.0f, 0.0f) and (1.0f, 1.0f) to display an entire textures.
        // Here are trying to display only a 32x32 pixels area of the texture, hence the UV computation.
        // Read about UV coordinates here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples


        //ImGuiIO& io = ImGui::GetIO();
        ////io.Fonts->AddFontDefault();

        //ImTextureID my_tex_id = io.Fonts->TexID;
        //float my_tex_w = (float)io.Fonts->TexWidth;
        //float my_tex_h = (float)io.Fonts->TexHeight;

        //ImVec2 size1 = ImVec2(20.0f, 20.0f);                        // Size of the image we want to make visible
        //ImVec2 uv0 = ImVec2(0.f, 0.f);                              // UV coordinates for lower-left
        //ImVec2 uv1 = ImVec2(my_tex_w, my_tex_h);                    // UV coordinates for (32,32) in our texture
        //ImVec2 size2 = ImVec2(20.0f, 20.0f);                        // Size of the image we want to make visible
        //ImVec2 uv2 = ImVec2(0.f, 0.f);                              // UV coordinates for lower-left
        //ImVec2 uv3 = ImVec2(my_tex_w, my_tex_h);                    // UV coordinates for (32,32) in our texture
        //ImVec2 size3 = ImVec2(20.0f, 20.0f);                        // Size of the image we want to make visible
        //ImVec2 uv4 = ImVec2(0.f, 0.f);                              // UV coordinates for lower-left
        //ImVec2 uv5 = ImVec2(my_tex_w, my_tex_h);                    // UV coordinates for (32,32) in our texturein our texture
        //
        //ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
        //ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
        //
        //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));
        //if (ImGui::ImageButton("Play", my_tex_id, size1, uv0, uv1, bg_col, tint_col))
        //{
        //    Serializer::GetInstance().SaveLevel(GSM::GameStateManager::GetInstance().GetCurrentLevel()->GetName());
        //    editorMode = Play;
        //}
        //if (ImGui::ImageButton("Edit", my_tex_id, size2, uv2, uv3, bg_col, tint_col))
        //{
        //    Serializer::GetInstance().LoadLevel(GSM::GameStateManager::GetInstance().GetCurrentLevel()->GetName());
        //    editorMode = Edit;
        //}
        //if (ImGui::ImageButton("Pause", my_tex_id, size3, uv4, uv5, bg_col, tint_col))
        //{
        //    editorMode = Pause;
        //}
        //ImGui::PopStyleVar();

        for (int i = 0; i < 20; i++)
            ImGui::Spacing();

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, editorMode == Play);
        if (ImGui::Button("Play"))
        {
            Serializer::GetInstance().SaveLevel(GSM::GameStateManager::GetInstance().GetCurrentLevel()->GetName());
            //save�� �ȵǾ� ���� �� �˾�
            
            editorMode = Play;
        }
        ImGui::PopItemFlag();
        ImGui::Spacing();
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, editorMode == Edit);
        if (ImGui::Button("Edit"))
        {
            editorMode = Edit;
            GameObjectManager::GetInstance().RemoveAllObject();
            Serializer::GetInstance().LoadLevel(GSM::GameStateManager::GetInstance().GetCurrentLevel()->GetName());
        }
        ImGui::PopItemFlag();
        ImGui::Spacing();
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, editorMode == Edit || editorMode == Pause);
        if (ImGui::Button("Pause"))
        {
            editorMode = Pause;
        }
        ImGui::PopItemFlag();
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
        if (ImGui::Begin(dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().
            GetCurrentLevel())->GetName().c_str(), p_open))
        {
            ImGui::SeparatorText("Object List");
            int id = 0;
            for (auto& obj : GameObjectManager::GetInstance().GetAllObjects())
            {
                if (ImGui::TreeNode(obj.first.c_str()))
                {
                    if (ImGui::IsItemHovered())
                    {
                        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                        {
                            editor_data.selectObjectName = obj.first;
                            editor_data.showObjectListRightClickPopup = true;
                        }
                    }
                    for (auto& comp : obj.second->GetComponents())
                    {
                        if (ImGui::TreeNode(comp.first.c_str()))
                        {
                            if (ImGui::IsItemHovered())
                            {
                                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                                {
                                    editor_data.selectObjectName = obj.first;
                                    editor_data.selectCompName = comp.first;
                                    editor_data.showCompListRightClickPopup = true;
                                }
                            }
                            comp.second->Edit();
                            ImGui::TreePop();
                        }
                        else
                        {
                            if (ImGui::IsItemHovered())
                            {
                                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                                {
                                    editor_data.selectObjectName = obj.first;
                                    editor_data.selectCompName = comp.first;
                                    editor_data.showCompListRightClickPopup = true;
                                }
                            }
                        }
                    }
                    //Combos
                    ImGui::Columns(2);
                    ImGui::Text("Layer : ");
                    ImGui::SameLine();
                    {
                        auto layers = GameObjectManager::GetInstance().GetLayers();

                        if (ImGui::BeginCombo("##Layer##", obj.second->GetLayer().c_str()))
                        {
                            for (int n = 0; n < (int)layers.size(); n++)
                            {
                                bool is_selected = (editor_data.layer_item_selected_idx == n);
                                if (ImGui::Selectable(layers.at(n).c_str(), is_selected))
                                {
                                    obj.second->SetLayer(layers.at(n));
                                    editor_data.layer_item_selected_idx = n;
                                }

                                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::NextColumn();
                    ImGui::Text("Tag : ");
                    ImGui::SameLine();
                    {
                        auto tags = GameObjectManager::GetInstance().GetTags();

                        if (ImGui::BeginCombo("##Tag##", obj.second->GetTag().c_str()))
                        {
                            for (int n = 0; n < (int)tags.size(); n++)
                            {
                                bool is_selected = (editor_data.tag_item_selected_idx == n);
                                if (ImGui::Selectable(tags.at(n).c_str(), is_selected))
                                {
                                    obj.second->SetTag(tags.at(n));
                                    editor_data.tag_item_selected_idx = n;
                                }

                                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::EndColumns();
                    //Buttons
                    ImGui::PushID(id);
                    ImGui::Columns(2);
                    {
                        if (ImGui::Button("Add Layer"))
                        {
                            editor_data.showAddLayerPopup = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Remove Layer"))
                        {
                            editor_data.showRemoveLayerPopup = true;
                        }
                    }
                    ImGui::NextColumn();
                    {
                        if (ImGui::Button("Add Tag"))
                        {
                            editor_data.showAddTagPopup = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Remove Tag"))
                        {
                            editor_data.showRemoveTagPopup = true;
                        }
                    }
                    ImGui::EndColumns();
                    ImGui::PopID();
                    id++;
                    ImGui::TreePop();
                }
                else
                {
                    if (ImGui::IsItemHovered())
                    {
                        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                        {
                            editor_data.selectObjectName = obj.first;
                            editor_data.showObjectListRightClickPopup = true;
                        }
                    }
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
                    std::cout << "����" << std::endl;
                else
                    std::cout << "����" << std::endl;
            }
        }
        ImGui::End(); 
    }
}

void editor::MainEditor::MainEditorInit(GLFWwindow* mainWindow)
{
    // Set Korean Font
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
