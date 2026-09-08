#include "platform.h"
#include <SDL3/SDL.h>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(title, windowWidth, windowHeight, 0, &window, &renderer);

    SDL_SetRenderLogicalPresentation(renderer, textureWidth, textureHeight, SDL_LOGICAL_PRESENTATION_STRETCH);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        textureWidth, textureHeight
    );

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
}

Platform::~Platform()
{
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Platform::Update(void const* buffer, int pitch)
{
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);

    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, texture, nullptr, nullptr);

    // 4. عرض الفريم
    SDL_RenderPresent(renderer);
}

bool Platform::ProcessInput(uint8_t* keys)
{
    bool quit = false;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                quit = true;
            } break;

            case SDL_EVENT_KEY_DOWN:
            {
                switch (event.key.key)
                {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_X: keys[0x0] = 1; break;
                    case SDLK_1: keys[0x1] = 1; break;
                    case SDLK_2: keys[0x2] = 1; break;
                    case SDLK_3: keys[0x3] = 1; break;
                    case SDLK_Q: keys[0x4] = 1; break;
                    case SDLK_W: keys[0x5] = 1; break;
                    case SDLK_E: keys[0x6] = 1; break;
                    case SDLK_A: keys[0x7] = 1; break;
                    case SDLK_S: keys[0x8] = 1; break;
                    case SDLK_D: keys[0x9] = 1; break;
                    case SDLK_Z: keys[0xA] = 1; break;
                    case SDLK_C: keys[0xB] = 1; break;
                    case SDLK_4: keys[0xC] = 1; break;
                    case SDLK_R: keys[0xD] = 1; break;
                    case SDLK_F: keys[0xE] = 1; break;
                    case SDLK_V: keys[0xF] = 1; break;
                }
            } break;

            case SDL_EVENT_KEY_UP:
            {
                switch (event.key.key)
                {
                    case SDLK_X: keys[0x0] = 0; break;
                    case SDLK_1: keys[0x1] = 0; break;
                    case SDLK_2: keys[0x2] = 0; break;
                    case SDLK_3: keys[0x3] = 0; break;
                    case SDLK_Q: keys[0x4] = 0; break;
                    case SDLK_W: keys[0x5] = 0; break;
                    case SDLK_E: keys[0x6] = 0; break;
                    case SDLK_A: keys[0x7] = 0; break;
                    case SDLK_S: keys[0x8] = 0; break;
                    case SDLK_D: keys[0x9] = 0; break;
                    case SDLK_Z: keys[0xA] = 0; break;
                    case SDLK_C: keys[0xB] = 0; break;
                    case SDLK_4: keys[0xC] = 0; break;
                    case SDLK_R: keys[0xD] = 0; break;
                    case SDLK_F: keys[0xE] = 0; break;
                    case SDLK_V: keys[0xF] = 0; break;
                }
            } break;
        }
    }

    return quit;
}