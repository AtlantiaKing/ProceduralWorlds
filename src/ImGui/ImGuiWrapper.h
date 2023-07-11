#pragma once

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace that
{
	class ImGuiWrapper final
	{
	public:
		ImGuiWrapper(SDL_Window* pWindow, SDL_Renderer* pRenderer);
		~ImGuiWrapper();

		void BeginDraw() const;
		void Draw() const;
		void EndDraw() const;

		void HandleInput(SDL_Event* pEvent) const;

		ImGuiWrapper(const ImGuiWrapper& other) = delete;
		ImGuiWrapper(ImGuiWrapper&& other) = delete;
		ImGuiWrapper& operator=(const ImGuiWrapper& other) = delete;
		ImGuiWrapper& operator=(ImGuiWrapper&& other) = delete;

	private:
	};
}

