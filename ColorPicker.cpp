#include "ColorPicker.h"

#include "imgui/imgui.h"

ColorPicker::ColorPicker():AUIScreen("COLOR_PICKER")
{
    open = false;
}

ColorPicker::~ColorPicker()
{
}

void ColorPicker::drawUI()
{
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

    static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

    static bool alpha_preview = true;
    static bool alpha_half_preview = false;
    static bool drag_and_drop = true;
    static bool options_menu = true;
    static bool hdr = false;
    static bool inputRGB = false;
    static bool inputHSV = false;

    ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | 
        (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | 
        (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
    
    if (open) {
        if (ImGui::Begin("Color Picker Screen"))
        {
            ImGui::SameLine();
            ImGui::ColorPicker4("Color", (float*)&color, misc_flags | ImGuiColorEditFlags_NoInputs);
            ImGui::SameLine();
            //ImGui::ColorButton("Current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
        }
        ImGui::End(); \
    }
}
