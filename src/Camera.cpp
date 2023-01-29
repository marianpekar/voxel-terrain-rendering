#include <math.h>
#include "Camera.h"

void Camera::ProcessInput(bool* isRunning, float deltaTime)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            *isRunning = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP)
            {
                x += cos(angle) * deltaTime * moveSpeed;
                y += sin(angle) * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                x -= cos(angle) * deltaTime * moveSpeed;
                y -= sin(angle) * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                angle -= 0.01 * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                angle += 0.01 * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_a)
            {
                height += 1 * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_d)
            {
                height -= 1 * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_s)
            {
                horizon += 1.5 * deltaTime * moveSpeed;
            }
            if (event.key.keysym.sym == SDLK_w)
            {
                horizon -= 1.5 * deltaTime * moveSpeed;
            }
            break;

        default:
            break;
    }
}
