#include "EasyImgui.h"

void MultiSelectCombo(const char* label, const std::vector<std::string>& items, std::vector<bool>& selected) 
{
    // 선택된 항목들의 이름을 합쳐서 레이블에 표시
    std::string preview;
    for (size_t i = 0; i < items.size(); ++i) {
        if (selected[i]) {
            if (!preview.empty()) preview += ", ";
            preview += items[i];
        }
    }

    // Combo 시작
    if (ImGui::BeginCombo(label, preview.empty() ? "Select..." : preview.c_str())) {
        // 전체 선택 / 전체 해제 버튼
        if (ImGui::Button("Select All")) {
            for (size_t i = 0; i < selected.size(); ++i) {
                selected[i] = true;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Deselect All")) {
            for (size_t i = 0; i < selected.size(); ++i) {
                selected[i] = false;
            }
        }

        // 스크롤 가능한 영역 시작
        ImGui::BeginChild("ComboScrollArea", ImVec2(0, 150), true); // 높이 150px 제한
        for (size_t i = 0; i < items.size(); ++i) {
            bool isSelected = selected[i];
            if(ImGui::Selectable(items[i].c_str(), &isSelected))
            {
                selected[i] = isSelected;
            }
        }
        ImGui::EndChild(); // 스크롤 영역 종료

        ImGui::EndCombo();
    }
}

void MultiSelectCombo(const char* label, std::map<std::string, bool>& items)
{ 
    // 선택된 항목들의 이름을 합쳐서 레이블에 표시
    std::string preview;
    for (auto& it : items)
    {
        if (it.second)
        {
            if (!preview.empty()) preview += ", ";
            preview += it.first;
        }
    }

    // Combo 시작
    if (ImGui::BeginCombo(label, preview.empty() ? "Select..." : preview.c_str())) {
        // 전체 선택 / 전체 해제 버튼
        if (ImGui::Button("Select All")) {
            for (auto& it : items) {
                it.second = true;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Deselect All")) {
            for (auto& it : items) {
                it.second = false;
            }
        }

        // 스크롤 가능한 영역 시작
        ImGui::BeginChild("ComboScrollArea", ImVec2(0, 150), true); // 높이 150px 제한
        for (auto& it : items) {
            bool isSelected = it.second;
            if (ImGui::Selectable(it.first.c_str(), &isSelected))
            {
                it.second = isSelected;
            }
        }
        ImGui::EndChild(); // 스크롤 영역 종료

        ImGui::EndCombo();
    }
}
