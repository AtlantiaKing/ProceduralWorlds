#include "ImGuiWrapper.h"

// ImGUI includes
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer.h>

// SDL includes
#include <SDL_image.h>

that::ImGuiWrapper::ImGuiWrapper(SDL_Window* window, SDL_Renderer* pRenderer)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer(window, pRenderer);
	ImGui_ImplSDLRenderer_Init(pRenderer);
}

that::ImGuiWrapper::~ImGuiWrapper()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void that::ImGuiWrapper::BeginDraw() const
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void that::ImGuiWrapper::Draw() const
{
	ImGui::Render();
}

void that::ImGuiWrapper::EndDraw() const
{
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void that::ImGuiWrapper::HandleInput(SDL_Event* pEvent) const
{
	ImGui_ImplSDL2_ProcessEvent(pEvent);
}
