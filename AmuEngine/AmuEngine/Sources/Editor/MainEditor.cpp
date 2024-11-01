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
#include "../Profiler/Profiler.h"
#include <vector>
#include <map>
#include <string>

editor::MainEditor::EditorMode editor::MainEditor::editorMode = Edit;

editor::MainEditor::EDITOR_DATA editor::MainEditor::editor_data;

editor::MainEditor::~MainEditor()
{
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
            if(!GameObjectManager::GetInstance().AddObject(editor_data.addObjName))
                editor_data.showAlreadyHaveSameNameObjectPopup = true;
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
                std::cout << "실패" << std::endl;
            else
                std::cout << "성공" << std::endl;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //같은 이름의 레벨이 있을 때 띄우는 팝업
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

    //같은 이름의 오브젝트가 있을 때 띄우는 팝업
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

    //Level 추가 팝업
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
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //컴포넌트 우클릭 팝업
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
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //레이어 추가 팝업
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
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //태그 추가 팝업
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
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //레벨 이름 변경 팝업
    if (editor_data.showChangeLevelPopup)
    {
        ImGui::OpenPopup("##Change Level##");
        editor_data.showChangeLevelPopup = false;
    }
    if (ImGui::BeginPopup("##Change Level##"))
    {
        if (ImGui::InputText("New Level Name", &editor_data.changeLvlName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //해당 이름이 중복되는 검사 후 적용
            if (LevelManager::GetInstance().ExistLevel(editor_data.changeLvlName))
            {
                // 중복 (이미 있는 거라고 띄움)
                std::cout << "실패" << std::endl;
                editor_data.showAlreadyHaveSameNameLevelPopup = true;
            }
            else
            {
                // 진행
                std::cout << "성공" << std::endl;
                LevelManager::GetInstance().ChangeLevel(editor_data.selectLevelName, editor_data.changeLvlName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //오브젝트 이름 변경 팝업
    if (editor_data.showChangeObjectPopup)
    {
        ImGui::OpenPopup("##Change Object##");
        editor_data.showChangeObjectPopup = false;
    }
    if (ImGui::BeginPopup("##Change Object##"))
    {
        if (ImGui::InputText("New Object Name", &editor_data.changeObjName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //해당 이름이 중복되는 검사 후 적용
            if (GameObjectManager::GetInstance().ExistObject(editor_data.changeObjName))
            {
                // 중복 (이미 있는 거라고 띄움)
                std::cout << "실패" << std::endl;
                editor_data.showAlreadyHaveSameNameObjectPopup = true;
            }
            else
            {
                // 진행
                std::cout << "성공" << std::endl;
                GameObjectManager::GetInstance().ChangeNameObject(editor_data.selectObjectName, editor_data.changeObjName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //레이어 이름 변경 팝업
    if (editor_data.showChangeLayerPopup)
    {
        ImGui::OpenPopup("##Change Layer##");
        editor_data.showChangeLayerPopup = false;
    }
    if (ImGui::BeginPopup("##Change Layer##"))
    {
        if (ImGui::InputText("New Layer Name", &editor_data.changeLayerName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //해당 이름이 중복되는 검사 후 적용
            if (GameObjectManager::GetInstance().ExistObjectLayer(editor_data.changeObjName))
            {
                // 중복 (이미 있는 거라고 띄움)
                std::cout << "실패" << std::endl;
                editor_data.showAlreadyHaveSameNameLayerPopup = true;
            }
            else
            {
                // 진행
                std::cout << "성공" << std::endl;
                GameObjectManager::GetInstance().ChangeNameLayer(editor_data.selectLayerName, editor_data.changeLayerName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //태그 이름 변경 팝업
    if (editor_data.showChangeTagPopup)
    {
        ImGui::OpenPopup("##Change Tag##");
        editor_data.showChangeTagPopup = false;
    }
    if (ImGui::BeginPopup("##Change Tag##"))
    {
        if (ImGui::InputText("New Tag Name", &editor_data.changeTagName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            //해당 이름이 중복되는 검사 후 적용
            if (GameObjectManager::GetInstance().ExistObjectTag(editor_data.changeTagName))
            {
                // 중복 (이미 있는 거라고 띄움)
                std::cout << "실패" << std::endl;
                editor_data.showAlreadyHaveSameNameTagPopup = true;
            }
            else
            {
                // 진행
                std::cout << "성공" << std::endl;
                GameObjectManager::GetInstance().ChangeNameTag(editor_data.selectTagName, editor_data.changeTagName);
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //레이어 콤보 우클릭 팝업
    if (editor_data.showLayerComboRightClickPopup)
    {
        ImGui::OpenPopup("##Layer Combo Right Click Popup##");
        editor_data.showLayerComboRightClickPopup = false;
    }
    if (ImGui::BeginPopup("##Layer Combo Right Click Popup##"))
    {
        bool enabled = true;
        if (GameObjectManager::GetInstance().ExistDefaultLayer(editor_data.selectLayerName))
        {
            enabled = false;
        }
        if (ImGui::MenuItem("Change Name", 0, nullptr, enabled))
        {
            editor_data.showChangeLayerPopup = true;
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::MenuItem("Remove Layer", 0, nullptr, enabled))
        {
            if (GameObjectManager::GetInstance().RemoveObjectLayer(editor_data.selectLayerName))
            {
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    //태그 콤보 우클릭 팝업
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
                // 성공
                std::cout << "성공" << std::endl;
            }
            else
            {
                // 실패
                std::cout << "실패" << std::endl;
            }
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
                    if (ImGui::MenuItem("Change Name", "Ctrl+C")) { //Change
                        editor_data.selectLevelName = lvl;
                        editor_data.showChangeLevelPopup = true;
                    }
                    ImGui::Separator();
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
                    ImGui::EndMenu();
                }
            }

            ImGui::SeparatorText("Level Option");

            if (ImGui::MenuItem("Save Level", "Ctrl+S")) {
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
            if (ImGui::MenuItem("Undo Level", "Ctrl+U")) {
                if (LevelManager::GetInstance().UndoLevel(editor_data.currLevelName))
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
            if (ImGui::MenuItem("Object Manager", "Ctrl+O", &editor_data.showAllObjects)) {

            }

            if (ImGui::MenuItem("Show Profiler", "Ctrl+P", &editor_data.showProfiler))
            {

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
            //save가 안되어 있을 시 팝업
            
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
                        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                        {
                            editor_data.selectObjectName = obj.first;
                        }
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
                            for (int n = 0; n < (int)layers.size(); n++)
                            {
                                ImGui::PushID(n);
                                if (ImGui::Selectable(layers.at(n).c_str(), false, ImGuiSelectableFlags_NoAutoClosePopups | ImGuiSelectableFlags_AllowOverlap))
                                {
                                    obj.second->SetLayer(layers.at(n));
                                    editor_data.layer_item_selected_idx = n;
                                }
                                if (ImGui::IsItemHovered()) //IsItemHoverd는 해당 코드의 상단의 아이템을 기준으로 작동된다.
                                {
                                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                                    {
                                        editor_data.selectLayerName = layers.at(n);
                                        editor_data.showLayerComboRightClickPopup = true;
                                    }
                                }
                                ImVec2 rs = ImGui::GetItemRectSize();
                                if (!GameObjectManager::GetInstance().ExistDefaultLayer(layers.at(n)))
                                {

                                    ImGui::BeginDisabled(GameObjectManager::GetInstance().GetLayers().front() == layers.at(n));
                                    ImGui::SameLine(rs.x - 60);
                                    if (ImGui::ArrowButton("##Layer Up##", ImGuiDir_Up))
                                    {
                                        GameObjectManager::GetInstance().OrderUpLayer(layers.at(n));
                                    }
                                    ImGui::EndDisabled();
                                    ImGui::BeginDisabled(GameObjectManager::GetInstance().GetLayers().back() == layers.at(n));
                                    ImGui::SameLine();
                                    if (ImGui::ArrowButton("##Layer Down##", ImGuiDir_Down))
                                    {
                                        GameObjectManager::GetInstance().OrderDownLayer(layers.at(n));
                                    }
                                    ImGui::EndDisabled();
                                }
                                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                                ImGui::PopID();
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
                                        editor_data.selectTagName = tags.at(n);
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
                        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                        {
                            editor_data.selectObjectName = obj.first;
                        }
                        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                        {
                            editor_data.selectObjectName = obj.first;
                            editor_data.showObjectListRightClickPopup = true;
                        }
                    }
                }
            }

            ImGui::SeparatorText("Object Option");
            ImGui::Columns(3, NULL, false);
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

            ImGui::NextColumn();
            static SpriteComp* psc = nullptr;
            static SpriteComp* sc = nullptr;
            
            if (!editor::MainEditor::editor_data.selectObjectName.empty())
            {
                if (sc)
                {
                    if (sc != psc)
                        psc = sc;
                }
                sc = GameObjectManager::GetInstance().
                    GetObj(editor::MainEditor::editor_data.selectObjectName)->
                    GetComponent<SpriteComp>();
            }

            if (ImGui::Checkbox("Trace Object", &editor::MainEditor::editor_data.IsTraceObject));
            if(editor::MainEditor::editor_data.IsTraceObject)
            {
                if (sc)
                {
                    if (psc)
                        psc->SetSelected(false);
                    sc->SetSelected(true);
                }
            }
        }
        ImGui::End(); 
    }
}


// utility structure for realtime plot
struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};

// utility structure for realtime plot
struct RollingBuffer {
    float Span;
    ImVector<ImVec2> Data;
    RollingBuffer() {
        Span = 10.0f;
        Data.reserve(2000);
    }
    void AddPoint(float x, float y) {
        float xmod = fmodf(x, Span);
        if (!Data.empty() && xmod < Data.back().x)
            Data.shrink(0);
        Data.push_back(ImVec2(xmod, y));
    }
};

static std::map<std::string, ScrollingBuffer*> sdata;
static std::map<std::string, RollingBuffer*> rdata;

void editor::MainEditor::ShowProfiler(bool* p_open)
{
    auto blocks = MyProfiler::Profiler::GetPtr()->GetBlocks();
    if (ImGui::Begin("Profiler", p_open))
    {
        static float profilerTime = 0;
        profilerTime += ImGui::GetIO().DeltaTime;
        //Frame, Camera, Logic, Engine, Bomb, Collision, Event, Level, Grahpic, GameObject
        double maxVal = 0;
        //Find Max value
        for (auto& block : blocks)
        {
            if (maxVal < block.second)
                maxVal = block.second;
        }
        for (auto& block : blocks)
        {
            //Normalize (0~1)
            float value = float(block.second / maxVal);

            if (sdata.find(block.first) == sdata.end())
            {
                ScrollingBuffer* sb = new ScrollingBuffer();
                sdata.insert({ block.first, sb });
            }
            sdata.find(block.first)->second->AddPoint(profilerTime, value);
            if (rdata.find(block.first) == rdata.end())
            {
                RollingBuffer* rb = new RollingBuffer();
                rdata.insert({ block.first, rb });
            }
            rdata.find(block.first)->second->AddPoint(profilerTime, value);
        }

        static float history = 10.0f;
        ImGui::SliderFloat("History", &history, 1, 30, "%.1f s");

        for (auto& data : rdata)
        {
            data.second->Span = history;
        }

        static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_Lock;
        
        if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1, 150))) {
            ImPlot::SetupAxes(nullptr, nullptr, flags, flags);
            ImPlot::SetupAxisLimits(ImAxis_X1, profilerTime - history, profilerTime, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
            ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
            for (auto& data : sdata)
            {
                //ImPlot::PlotShaded(data.first.c_str(), &data.second->Data[0].x, &data.second->Data[0].y, data.second->Data.size(), -INFINITY, 0, data.second->Offset, 2 * sizeof(float));
                ImPlot::PlotLine(data.first.c_str(), &data.second->Data[0].x, &data.second->Data[0].y, data.second->Data.size(), 0, data.second->Offset, 2 * sizeof(float));
                //std::cout << data.first.c_str() << " | " << data.second->Data[0].x << " | " << data.second->Data[0].y << " | " << data.second->Data.size() << std::endl;
            }
            //ImPlot::PlotShaded("Mouse X", &sdata1.Data[0].x, &sdata1.Data[0].y, sdata1.Data.size(), -INFINITY, 0, sdata1.Offset, 2 * sizeof(float));
            //ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2 * sizeof(float));
            ImPlot::EndPlot();
        }
        if (ImPlot::BeginPlot("##Rolling", ImVec2(-1, 150))) {
            ImPlot::SetupAxes(nullptr, nullptr, flags, flags);
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, history, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 1);
            for (auto& data : rdata)
            {
                ImPlot::PlotLine(data.first.c_str(), &data.second->Data[0].x, &data.second->Data[0].y, data.second->Data.size(), 0, 0, 2 * sizeof(float));
            }
            //ImPlot::PlotLine("Mouse X", &rdata1.Data[0].x, &rdata1.Data[0].y, rdata1.Data.size(), 0, 0, 2 * sizeof(float));
            //ImPlot::PlotLine("Mouse Y", &rdata2.Data[0].x, &rdata2.Data[0].y, rdata2.Data.size(), 0, 0, 2 * sizeof(float));
            ImPlot::EndPlot();
        }
    }
    ImGui::End();
    if (*p_open == false)
    {
        for (auto& data : sdata)
        {
            delete data.second;
        }
        sdata.clear();
        for (auto& data : rdata)
        {
            delete data.second;
        }
        rdata.clear();
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
    if (editor_data.showProfiler) { ShowProfiler(&editor_data.showProfiler); }
}

void editor::MainEditor::MainEditorExit()
{
}
