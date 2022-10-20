#include "Viewport.h"
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

void Viewport::initialize(SwapChain* swap_chain)
{
    this->swapChain = swap_chain;
}

void Viewport::destroy()
{
	delete this;
}

void Viewport::update(const char* name)
{
    if (swapChain != NULL) {
        ImGui::Begin(name);
        ImGui::Text("%s", name);

        //ImGui::Image();

        ImGui::Text("%s", name);
        ImGui::End();
    }
    
}

