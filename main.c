#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("\nAn error occured:%s\n", SDL_GetError());
    }

    SDL_Window *window;
    window = SDL_CreateWindow("text", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        printf("\nerror is %s\n", SDL_GetError());
    }
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0xFF, 0xFF, 0xFF, 1));
    SDL_UpdateWindowSurface(window);

    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = SDL_TRUE;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
