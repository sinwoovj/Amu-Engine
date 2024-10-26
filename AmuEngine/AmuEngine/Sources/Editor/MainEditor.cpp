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
            Serializer::GetInstance().SaveEditorSetting();
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
        if (ImGui::MenuItem("Change Name")) {
            editor_data.showChangeObjectPopup = true;
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
        ImGui::Separator();
        if (ImGui::MenuItem("Delete Object", NULL))
        {
            GameObjectManager::GetInstance().RemoveObject(editor_data.selectObjectName);
            if (GameObjectManager::GetInstance().GetObj(editor_data.selectObjectName) != nullptr)
                std::cout << "����" << std::endl;
            else
                std::cout << "����" << std::endl;
            ImGui::CloseCurrentPopup();
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

    //���� �̸� ���� �˾�
    if (editor_data.showChangeLevelPopup)
    {
        ImGui::OpenPopup("##Change Level##");
        editor_data.showChangeLevelPopup = false;
    }
    if (ImGui::BeginPopup("##Change Level##"))
    {
        if (ImGui::InputText("New Level Name", &editor_data.changeLvlName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //�ش� �̸��� �ߺ��Ǵ� �˻� �� ����
            if (LevelManager::GetInstance().ExistLevel(editor_data.changeLvlName))
            {
                // �ߺ� (�̹� �ִ� �Ŷ�� ���)
                std::cout << "����" << std::endl;
                editor_data.showAlreadyHaveSameNameLevelPopup = true;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
                LevelManager::GetInstance().ChangeLevel(editor_data.selectLevelName, editor_data.changeLvlName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //������Ʈ �̸� ���� �˾�
    if (editor_data.showChangeObjectPopup)
    {
        ImGui::OpenPopup("##Change Object##");
        editor_data.showChangeObjectPopup = false;
    }
    if (ImGui::BeginPopup("##Change Object##"))
    {
        if (ImGui::InputText("New Object Name", &editor_data.changeObjName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //�ش� �̸��� �ߺ��Ǵ� �˻� �� ����
            if (GameObjectManager::GetInstance().ExistObject(editor_data.changeObjName))
            {
                // �ߺ� (�̹� �ִ� �Ŷ�� ���)
                std::cout << "����" << std::endl;
                editor_data.showAlreadyHaveSameNameObjectPopup = true;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
                GameObjectManager::GetInstance().ChangeNameObject(editor_data.selectObjectName, editor_data.changeObjName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //���̾� �̸� ���� �˾�
    if (editor_data.showChangeLayerPopup)
    {
        ImGui::OpenPopup("##Change Layer##");
        editor_data.showChangeLayerPopup = false;
    }
    if (ImGui::BeginPopup("##Change Layer##"))
    {
        if (ImGui::InputText("New Layer Name", &editor_data.changeLayerName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //�ش� �̸��� �ߺ��Ǵ� �˻� �� ����
            if (GameObjectManager::GetInstance().ExistObjectLayer(editor_data.changeObjName))
            {
                // �ߺ� (�̹� �ִ� �Ŷ�� ���)
                std::cout << "����" << std::endl;
                editor_data.showAlreadyHaveSameNameLayerPopup = true;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
                GameObjectManager::GetInstance().ChangeNameLayer(editor_data.selectLayerName, editor_data.changeLayerName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //�±� �̸� ���� �˾�
    if (editor_data.showChangeTagPopup)
    {
        ImGui::OpenPopup("##Change Tag##");
        editor_data.showChangeTagPopup = false;
    }
    if (ImGui::BeginPopup("##Change Tag##"))
    {
        if (ImGui::InputText("New Tag Name", &editor_data.changeTagName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //�ش� �̸��� �ߺ��Ǵ� �˻� �� ����
            if (GameObjectManager::GetInstance().ExistObjectTag(editor_data.changeTagName))
            {
                // �ߺ� (�̹� �ִ� �Ŷ�� ���)
                std::cout << "����" << std::endl;
                editor_data.showAlreadyHaveSameNameTagPopup = true;
            }
            else
            {
                // ����
                std::cout << "����" << std::endl;
                GameObjectManager::GetInstance().ChangeNameTag(editor_data.selectTagName, editor_data.changeTagName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //���̾� �޺� ��Ŭ�� �˾�
    if (editor_data.showLayerComboRightClickPopup)
    {
        ImGui::OpenPopup("##Layer Combo Right Click Popup##");
        editor_data.showLayerComboRightClickPopup = false;
    }
    if (ImGui::BeginPopup("##Layer Combo Right Click Popup##"))
    {
        bool selected = false;
        bool enabled = true;
        if (!GameObjectManager::GetInstance().ExistDefaultLayer(editor_data.selectLayerName))
        {
            enabled = false;
        }
        if (ImGui::MenuItem("Change Name", 0, selected, enabled))
        {
            editor_data.showChangeLayerPopup = true;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("Remove Layer", 0, selected, enabled))
        {
            if (GameObjectManager::GetInstance().RemoveObjectLayer(editor_data.selectLayerName))
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

    //�±� �޺� ��Ŭ�� �˾�
    if (editor_data.showTagComboRightClickPopup)
    {
        ImGui::OpenPopup("##Tag Combo Right Click Popup##");
        editor_data.showTagComboRightClickPopup = false;
    }
    if (ImGui::BeginPopup("##Tag Combo Right Click Popup##"))
    {
        bool selected = false;
        bool enabled = true;
        if (GameObjectManager::GetInstance().ExistDefaultTag(editor_data.selectTagName))
        {
            enabled = false;
        }
        if (ImGui::MenuItem("Change Name", 0, selected, enabled))
        {
            editor_data.showChangeTagPopup = true;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("Remove Tag", 0, selected, enabled))
        {
            if (GameObjectManager::GetInstance().RemoveObjectTag(editor_data.selectTagName))
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
                    if (ImGui::MenuItem("Change Name", "Ctrl+C")) { //Change
                        editor_data.selectLevelName = lvl;
                        editor_data.showChangeLevelPopup = true;
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

        for (int i = 0; i < 20; i++)
            ImGui::Spacing();

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, editorMode == Play);
        if (ImGui::Button("Play"))
        {
            Serializer::GetInstance().SaveLevel(GSM::GameStateManager::GetInstance().GetCurrentLevel()->GetName());
            Serializer::GetInstance().SaveEditorSetting();
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
            Serializer::GetInstance().LoadEditorSetting();
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

                        bool isLayerExistNow = false;
                        for (auto& layer : layers)
                        {
                            if (obj.second->GetLayer() == layer)
                            {
                                isLayerExistNow = true;
                                break;
                            }
                        }
                        if (!isLayerExistNow)
                            obj.second->SetLayer(*GameObjectManager::GetInstance().DefaultLayer.begin());

                        if (ImGui::BeginCombo("##Layer##", obj.second->GetLayer().c_str()))
                        {
                            bool is_selected;
                            for (int n = 0; n < (int)layers.size(); n++)
                            {
                                if (ImGui::IsItemHovered())
                                {
                                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                                    {
                                        editor_data.selectLayerName = obj.first;
                                        editor_data.showLayerComboRightClickPopup = true;
                                    }
                                }
                                is_selected = (editor_data.layer_item_selected_idx == n);
                                if (ImGui::Selectable(layers.at(n).c_str(), is_selected))
                                {
                                    obj.second->SetLayer(layers.at(n));
                                    editor_data.layer_item_selected_idx = n;
                                }
                                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            //Add List
                            ImGui::Separator();
                            if (ImGui::Selectable("Add Layer"))
                            {
                                editor_data.showAddLayerPopup = true;
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::NextColumn();
                    ImGui::Text("Tag : ");
                    ImGui::SameLine();
                    {
                        auto tags = GameObjectManager::GetInstance().GetTags();

                        bool isTagExistNow = false;
                        for (auto& tag : tags)
                        {
                            if (obj.second->GetTag() == tag)
                                isTagExistNow = true;
                        }
                        if (!isTagExistNow)
                            obj.second->SetTag(*GameObjectManager::GetInstance().DefaultTag.begin());

                        if (ImGui::BeginCombo("##Tag##", obj.second->GetTag().c_str()))
                        {
                            bool is_selected;
                            for (int n = 0; n < (int)tags.size(); n++)
                            {
                                if (ImGui::IsItemHovered())
                                {
                                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                                    {
                                        editor_data.selectTagName = obj.first;
                                        editor_data.showTagComboRightClickPopup = true;
                                    }
                                }
                                is_selected = (editor_data.tag_item_selected_idx == n);
                                if (ImGui::Selectable(tags.at(n).c_str(), is_selected))
                                {
                                    obj.second->SetTag(tags.at(n));
                                    editor_data.tag_item_selected_idx = n;
                                }

                                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                                if (is_selected)
                                    ImGui::SetItemDefaultFocus();
                            }
                            //Add Tag
                            ImGui::Separator();
                            is_selected = (editor_data.tag_item_selected_idx == (int)tags.size());
                            if (ImGui::Selectable("Add Tag", is_selected))
                            {
                                editor_data.showAddTagPopup = true;
                                editor_data.tag_item_selected_idx = (int)tags.size();
                            }
                            ImGui::EndCombo();
                        }
                    }
                    ImGui::EndColumns();
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
