#include "PerspectiveView.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "imgui/imgui.h"

PerspectiveView::PerspectiveView() :AUIScreen("PERSPECTIVE_VIEW")
{
    open = false;
}

PerspectiveView::~PerspectiveView()
{
}

void PerspectiveView::drawUI()
{
    if (open) {
        ImGui::Begin("Perspective View");
        ImGui::Image(GraphicsEngine::getInstance()->getRenderedTexture()->GetShaderResourceView(), ImVec2(512, 512));
        ImGui::End();
    }
}
