#include "GameView.h"
#include "imgui/imgui.h"
#include "GraphicsEngine.h"
#include "RenderTexture.h"

GameView::GameView() :AUIScreen("GAME_VIEW")
{
    open = false;
}

GameView::~GameView()
{
}

void GameView::drawUI()
{
    if (open) {
        ImGui::Begin("Game View");
        ImGui::Image(GraphicsEngine::getInstance()->getRenderedTexture()->GetShaderResourceView(), ImVec2(512, 512));
        ImGui::End();
    }
}
