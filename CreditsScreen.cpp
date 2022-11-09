#include "CreditsScreen.h"

#include "imgui/imgui.h"

CreditsScreen::CreditsScreen() :AUIScreen("CREDITS_SCREEN")
{
    open = false;
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
    if (open) {
        ImGui::Begin("Credits");
        ImGui::Text("GDENG-2 Game Engine");
        ImGui::Text("Developed by:");
        ImGui::Text("Vincent Eugene Tan");
        ImGui::Text("Special Thanks to:");
        ImGui::BulletText("Our Prof, Sir Neil Patrick Del Gallego!");
        ImGui::BulletText("PardCode: https://www.youtube.com/c/PardCode");
        ImGui::BulletText("The Cherno: https://www.youtube.com/c/TheChernoProject");
        ImGui::BulletText("ocornut's ImGUI: https://github.com/ocornut/imgui");
        ImGui::End();
    }


}
