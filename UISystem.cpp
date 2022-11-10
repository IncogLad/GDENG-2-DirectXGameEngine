#include "UISystem.h"

#include "ColorPicker.h"
#include "CreditsScreen.h"
#include "GameView.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_win32.h"
#include "imgui\imgui_impl_dx11.h"
#include "GraphicsEngine.h"
#include "TextureManager.h"
#include "MenuToolBar.h"

UISystem* UISystem::sharedInstance = nullptr;

UISystem::UISystem()
{
}

UISystem::~UISystem()
{
}

void UISystem::initialize()
{
    sharedInstance = new UISystem();
}

UISystem* UISystem::getInstance()
{
    return sharedInstance;
}

void UISystem::initImGUI(HWND hwnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->m_d3d_device, GraphicsEngine::getInstance()->m_imm_context);

    //wood = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\dlsu.png");

    CreditsScreen* credits_screen = new CreditsScreen();
    uiTable[uiNames.CREDITS_SCREEN] = credits_screen;
    uiList.push_back(credits_screen);

    MenuToolBar* menu_tool_bar = new MenuToolBar();
    uiTable[uiNames.MENU_TOOL_BAR] = menu_tool_bar;
    uiList.push_back(menu_tool_bar);

    GameView* game_view = new GameView();
    uiTable[uiNames.GAME_VIEW] = game_view;
    uiList.push_back(game_view);

    ColorPicker* color_picker = new ColorPicker();
    uiTable[uiNames.COLOR_PICKER] = color_picker;
    uiList.push_back(color_picker);

}

void UISystem::updateNewFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}

void UISystem::update()
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
	
    
    for (auto const& i : uiList) {
        i->drawUI();
    }

    /*ImGui::Begin("Test");
    ImGui::Image(wood->getShaderResourceView(), ImVec2(500, 500));
    ImGui::End();*/
    // Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

}

void UISystem::destroy()
{
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    delete sharedInstance;
} 
