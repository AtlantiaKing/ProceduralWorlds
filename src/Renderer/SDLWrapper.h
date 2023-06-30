#pragma once

#include "../Structs/Vector2.h"
#include "../Structs/Color.h"

#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace that
{
	class SDLWrapper final
	{
	public:
		SDLWrapper(int width, int height);
		~SDLWrapper();

		SDLWrapper(const SDLWrapper& other) = delete;
		SDLWrapper(SDLWrapper&& other) = delete;
		SDLWrapper& operator=(const SDLWrapper& other) = delete;
		SDLWrapper& operator=(SDLWrapper&& other) = delete;

		void Draw() const;
		bool HandleEvent() const;

		void DrawPixel(const Vector2Int& coordinate, const Color& color);

	private:
		void UpdateTexture() const;

		SDL_Window* m_pWindow{};
		SDL_Renderer* m_pRenderer{};
		SDL_Texture* m_pTexture{};

		std::vector<Color> m_PixelBuffer{};

		const Color m_ClearColor{ 190, 220, 220, 255 };

		int m_Width{};
		int m_Height{};
	};
}
