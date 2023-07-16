#include "SDLWrapper.h"

#include "SDL.h"
#include "SDL_image.h"

//#include "ImGui/ImGuiWrapper.h"

sdlw::SDLWrapper::SDLWrapper(int width, int height)
    : m_Width{ width }, m_Height{ height }
{
    // Initialize the SDL library
    SDL_Init(SDL_INIT_VIDEO);

    // Create a new window with the given size at a undefined position
    m_pWindow = SDL_CreateWindow("Procedular Worlds", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    // Create an SDL renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

    // Enable alpha blending in the renderer
    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

    // Create a texture that has the size of the screen
    m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    // Enable alpha blending in the texture
    SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

    // Create a pixel buffer for this texture
    const size_t textureSize = static_cast<size_t>(width) * static_cast<size_t>(height);
    m_PixelBuffer.resize(textureSize, Color{});
}

sdlw::SDLWrapper::~SDLWrapper()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void sdlw::SDLWrapper::DrawClearColor() const
{
    // Render clear color
    SDL_SetRenderDrawColor(m_pRenderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 0);
    SDL_RenderClear(m_pRenderer);
}

void sdlw::SDLWrapper::DrawTexture() const
{    
    // Update the latest changes to the texture
    UpdateTexture();

    // Render the texture
    SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, nullptr);
}

void sdlw::SDLWrapper::SwapBuffer() const
{
    // Render the current buffer
    SDL_RenderPresent(m_pRenderer);
}

bool sdlw::SDLWrapper::HandleEvent() const
{
    SDL_Event event; 
    while (SDL_PollEvent(&event))
    {
        // This function should notify the main to stop if SDL_QUIT has been received
        if (event.type == SDL_QUIT) return false;
    }

    return true;
}

that::Vector2Int sdlw::SDLWrapper::GetWindowSize() const
{
    return that::Vector2Int{ m_Width, m_Height };
}

SDL_Window* sdlw::SDLWrapper::GetWindow() const
{
    return m_pWindow;
}

SDL_Renderer* sdlw::SDLWrapper::GetRenderer() const
{
    return m_pRenderer;
}

void sdlw::SDLWrapper::DrawPixel(const that::Vector2Int& coordinate, const Color& color)
{
    // Update the pixel inside the buffer
    const size_t coordinateId{ static_cast<size_t>(coordinate.y) * m_Width + static_cast<size_t>(coordinate.x) };
    
    Color& colorOnCoord{ m_PixelBuffer[coordinateId] };

    const float alphaPercentage{ static_cast<float>(color.a) / UINT8_MAX };
    const float inverseAlphaPercentage{ 1.0f - alphaPercentage };

    colorOnCoord.r = static_cast<uint8_t>(color.r * alphaPercentage + colorOnCoord.r * inverseAlphaPercentage);
    colorOnCoord.g = static_cast<uint8_t>(color.g * alphaPercentage + colorOnCoord.g * inverseAlphaPercentage);
    colorOnCoord.b = static_cast<uint8_t>(color.b * alphaPercentage + colorOnCoord.b * inverseAlphaPercentage);
    colorOnCoord.a = std::max(color.a, colorOnCoord.a);
}

void sdlw::SDLWrapper::UpdateTexture() const
{
    // Copy the pixel buffer to the texture
    SDL_UpdateTexture(m_pTexture, nullptr, m_PixelBuffer.data(), m_Width * sizeof(Color));
}
