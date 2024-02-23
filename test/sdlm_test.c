/*
	Copyright (c) 2024 zxsvrx
	
	This software is provided ‘as-is’, without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	
	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
	
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	
	3. This notice may not be removed or altered from any source
	distribution.
*/

#include <SDL2/SDL.h>

#include "SDLM_Timer.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

SDL_Rect rect = {0, 0, 64, 64};

void draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);

	rect.x += 10;

	if (rect.x > 1000 + rect.w) {
		rect.x = -rect.w;
	}
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    	fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    	return 1;
    }

    window = SDL_CreateWindow("SDLM Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDLM_Timer timer = {
    	.repeat = SDLM_TRUE,
    	.time = 1.0/60.0
    };
    
    SDLM_Timer_StartRunLoopTimer(&timer, draw);


    SDL_Event event;
    SDL_bool quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
        }
    }

    SDLM_Timer_InvalidateTimer(&timer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
