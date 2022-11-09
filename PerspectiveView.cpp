#include "PerspectiveView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "imgui/imgui.h"

PerspectiveView::PerspectiveView() :AUIScreen("PERSPECTIVE_VIEW")
{
}

PerspectiveView::~PerspectiveView()
{
}

void PerspectiveView::drawUI()
{
    ImGui::Begin("Game View");
    ImGui::Image(GraphicsEngine::getInstance()->getRenderedTexture()->GetShaderResourceView(), ImVec2(512, 512));
    ImGui::End();
}
