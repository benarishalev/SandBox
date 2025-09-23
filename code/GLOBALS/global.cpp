#include "global.hpp"

int Global::WIDTH = 0;
int Global::HEIGHT = 0;
SDL_Renderer* Global::renderer;
SDL_Window* Global::window;
std::string Global::mode = "gameloop";

void Global::init(const int width, const int height) {
    SDL_Init(SDL_INIT_VIDEO);
    WIDTH = width;
    HEIGHT = height;
    window = SDL_CreateWindow("My Game", WIDTH, HEIGHT, 0); 
    renderer = SDL_CreateRenderer(window, 0);
}

void Global::quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Global::cleanWindow() {
    SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Global::presentWindow() {
    SDL_RenderPresent(renderer);
}

void Global::runLoop() {
    SDL_Event event;
    bool running = true;
    while (running) {
        if (mode == "gameloop") {
            runGameLoop();
        } else if (mode == "quit") {
            running = false;
        }
    }
    quit();
}

void Global::runGameLoop() {
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                mode = "quit";
            }
        }

        cleanWindow();

        presentWindow();
    }
}