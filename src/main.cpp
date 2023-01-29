#include <iostream>
#include "Renderer.h"
#include "Camera.h"
#include "Map.h"

int main(int argc, char* args[])
{
    Renderer* renderer = new Renderer();

    if (!renderer->Setup())
    {
        return -1;
    }

    Camera* camera = new Camera();
    Map* map = new Map("../maps/colormap.gif", "../maps/heightmap.gif");

    constexpr Uint32 FPS = 144;
    constexpr Uint32 FRAME_TIME_LENGTH = (1000 / FPS);

    Uint32 ticksLastFrame = 0;
    bool isRunning = true;
    while (isRunning)
    {
        const float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
        ticksLastFrame = SDL_GetTicks();

        camera->ProcessInput(&isRunning, deltaTime);

        renderer->ClearScreen(0xFF3492eb);
        map->Draw(renderer, camera);
        renderer->Render();

        SDL_Delay(FRAME_TIME_LENGTH);
    }

    delete renderer;
    delete camera;
    delete map;
}
