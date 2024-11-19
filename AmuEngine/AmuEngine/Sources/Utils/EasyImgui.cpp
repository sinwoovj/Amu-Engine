#include "EasyImgui.h"

void MultiSelectCombo(const char* label, const std::vector<std::string>& items, std::vector<bool>& selected) 
{
    // ���õ� �׸���� �̸��� ���ļ� ���̺� ǥ��
    std::string preview;
    for (size_t i = 0; i < items.size(); ++i) {
        if (selected[i]) {
            if (!preview.empty()) preview += ", ";
            preview += items[i];
        }
    }

    // Combo ����
    if (ImGui::BeginCombo(label, preview.empty() ? "Select..." : preview.c_str())) {
        // ��ü ���� / ��ü ���� ��ư
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

        // ��ũ�� ������ ���� ����
        ImGui::BeginChild("ComboScrollArea", ImVec2(0, 150), true); // ���� 150px ����
        for (size_t i = 0; i < items.size(); ++i) {
            bool isSelected = selected[i];
            if(ImGui::Selectable(items[i].c_str(), &isSelected))
            {
                selected[i] = isSelected;
            }
        }
        ImGui::EndChild(); // ��ũ�� ���� ����

        ImGui::EndCombo();
    }
}