#include "TopdownView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "imgui/imgui.h"

TopdownView::TopdownView() :AUIScreen("TOPDOWN_VIEW")
{
}

TopdownView::~TopdownView()
{
}

void TopdownView::drawUI()
{
    ImGui::Begin("Game View");
    ImGui::Image(GraphicsEngine::getInstance()->getRenderedTexture()->GetShaderResourceView(), ImVec2(512, 512));
    ImGui::End();
}
