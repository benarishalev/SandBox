#include "global.hpp"

int Global::WIDTH = 0;
int Global::HEIGHT = 0;
SDL_Renderer* Global::renderer;
SDL_Window* Global::window;
std::string Global::mode = "gameloop";

// gameloop
int Global::GRID_SIZE = 50;
std::vector<std::unique_ptr<Material>> Global::materials;

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


void Global::addMaterialToMouse(int xPos, int yPos, int size) {
    int idxX = (int)(xPos/GRID_SIZE);
    int idxY = (int)(yPos/GRID_SIZE);

    for (int y = idxY-size/2; y < idxY+size; y++) {
        for (int x = idxX-size/2; x < idxX+size; x++) {
            materials.push_back(std::make_unique<Water>(Point(x, y)));
        }
    }
}

void Global::drawRect(SDL_Color color, float x, float y, float width, float height, bool fill) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = {x, y, width, height};
    if (fill) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderRect(renderer, &rect);
    }
}

void Global::drawGrid(SDL_Color color) {
    for (int y = 0; y < HEIGHT; y += GRID_SIZE) {
        for (int x = 0; x < WIDTH; x += GRID_SIZE) {
            drawRect(color, x, y, GRID_SIZE, GRID_SIZE, false);
        }
    }
}

void Global::drawMaterials() {
    for (int i = 0; i < materials.size(); i++) {
        materials[i]->Draw();
    }
}

void Global::moveMaterials() {
    for (int i = 0; i < materials.size(); i++) {
        materials[i]->Move();
    }
}

void Global::runGameLoop() {
    SDL_Event event;
    bool running = true;

    int timer = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                mode = "quit";
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float x, y;
                SDL_GetMouseState(&x, &y);
                addMaterialToMouse(x, y, 2);
            }
        }

        timer++;
        
        if (timer >= 200) {
            moveMaterials();
            timer = 0;
        }

        cleanWindow();

        drawMaterials();

        drawGrid({50, 50, 50, 255});

        presentWindow();
    }
}