#include "Viewport.h"

#include "GraphicsEngine.h"
#include "RenderTexture.h"
#include "UISystem.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_win32.h"
#include "imgui\imgui_impl_dx11.h"

Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

void Viewport::initialize()
{
   
}

void Viewport::destroy()
{
	delete this;
}

void Viewport::update(const char* name)
{
        ImGui::Begin(name);
        ImGui::Text("%s", name);

        

        ImGui::Image(GraphicsEngine::getInstance()->getRenderedTexture()->GetShaderResourceView(), ImVec2(500, 500));

        ImGui::Text("%s", name);
        ImGui::End();
    
    
}

