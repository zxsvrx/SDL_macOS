# SDL_macOS
A repository containing a simple fix for the SDL2(3) main loop freeze when resizing or interacting with the macos window and menubar.

### How to use SDLM_Timer

```c
#include <SDL2/SDL.h>

#include "SDLM_Timer.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
SDL_bool quit = SDL_FALSE;

void draw() {
    // render shapes and textures
}

int main() {
    // initialize sdl and create window + renderer

    SDLM_Timer timer = {
        // timer should repeat
    	.repeat = SDLM_TRUE,
        // 1/60 ≈ 60FPS
    	.time = 1.0/60.0
    };
    
    // create timer
    SDLM_Timer_StartRunLoopTimer(&timer, draw);

    while (!quit) {
        // handle events
    }
    
    // invalidate (stop and free) timer
    SDLM_Timer_InvalidateTimer(&timer);
    
    // clean up

    return 0;
}
```
