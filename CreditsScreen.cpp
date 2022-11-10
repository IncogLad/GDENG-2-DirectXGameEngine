#include "CreditsScreen.h"
#include "ResourceManager.h"
#include "imgui/imgui.h"
#include "GraphicsEngine.h"
#include "TextureManager.h"

CreditsScreen::CreditsScreen() :AUIScreen("CREDITS_SCREEN")
{
    open = false;
    logoImage = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\dlsu.png");
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
    if (open) {
        ImGui::Begin("Credits");
        //put logo image texture here
    	ImGui::Image(logoImage->getShaderResourceView(), ImVec2(200,200));
        
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
