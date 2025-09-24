#include "global.hpp"

int Global::WIDTH = 0;
int Global::HEIGHT = 0;
SDL_Renderer* Global::renderer;
SDL_Window* Global::window;
std::string Global::mode = "gameloop";

// all
Point Global::mousePosition = Point(0, 0);

// gameloop
int Global::GRID_SIZE = 40;
Point Global::gridDimenstion = Point(30, 30);
int Global::gameSpeed = 50;
int Global::spawnSize = 2;
std::vector<std::unique_ptr<Material>> Global::materials;
std::vector<std::vector<std::string>> Global::materialGrid;
int Global::timer = 0;
std::map<std::string, std::unique_ptr<Material>> Global::prototypeMaterials;
std::string Global::currentMaterial = "water";
std::vector<Button> Global::buttons;

void Global::init(const int width, const int height) {
    SDL_Init(SDL_INIT_VIDEO);
    WIDTH = width;
    HEIGHT = height;
    window = SDL_CreateWindow("SandBox", WIDTH, HEIGHT, 0); 
    renderer = SDL_CreateRenderer(window, 0);

    // init prototype materials
    prototypeMaterials["sand"] = std::make_unique<Sand>(Point(0, 0));
    prototypeMaterials["water"] = std::make_unique<Water>(Point(0, 0));
    prototypeMaterials["stone"] = std::make_unique<Stone>(Point(0, 0));

    // init buttons
    int x = 0;
    int y = 0;
    for (const auto& [key, value] : prototypeMaterials) {
        buttons.push_back(Button(Point(GRID_SIZE*gridDimenstion.x+x*100+10, y*50+10), Point(100, 50), value->color, value->type));
        if (y >= ((gridDimenstion.y-2)*GRID_SIZE/50)) {y = 0; x++;}
        else {y++;}
    }

    // init material grid
    materialGrid.resize(gridDimenstion.y);
    for (int i = 0; i < gridDimenstion.y; i++) {
        materialGrid[i].resize(gridDimenstion.x);
    }
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


void Global::addMaterialToMouse(int xPos, int yPos) {
    int idxX = (int)(xPos/GRID_SIZE);
    int idxY = (int)(yPos/GRID_SIZE);

    for (int y = idxY-spawnSize/2; y < idxY+spawnSize; y++) {
        for (int x = idxX-spawnSize/2; x < idxX+spawnSize; x++) {
            if (x < 0 || x >= gridDimenstion.x || y < 0 || y >= gridDimenstion.y) {
                continue;
            }
            std::unique_ptr<Material> material = prototypeMaterials[currentMaterial]->clone();\
            material->position = Point(x, y);
            materials.push_back(std::move(material));
            materialGrid[y][x] = currentMaterial;
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
    for (int y = 0; y < gridDimenstion.y; y += 1) {
        for (int x = 0; x < gridDimenstion.x; x += 1) {
            drawRect(color, x*GRID_SIZE, y*GRID_SIZE, GRID_SIZE, GRID_SIZE, false);
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
        materialGrid[materials[i]->position.y][materials[i]->position.x] = "";
        materials[i]->Move();
        materialGrid[materials[i]->position.y][materials[i]->position.x] = materials[i]->type;
    }
}

void Global::setMousePosition() {
    float x, y;
    SDL_GetMouseState(&x, &y);
    mousePosition = Point(x, y);
}

Uint8 Global::getColorValue(Uint8 value, int change) {
    int newValue = value + change;
    if (newValue < 0) {
        newValue = 0;
    } else if (newValue > 255) {
        newValue = 255;
    }
    return static_cast<Uint8>(newValue);
}

void Global::drawButtons() {
    for (auto& button : buttons) {
        button.Draw();
    }
}

void Global::runGameLoop() {
    SDL_Event event;
    bool running = true;

    timer = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
                mode = "quit";
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                addMaterialToMouse(mousePosition.x, mousePosition.y);

                for (auto& button : buttons) {
                    if (button.isHover()) {
                        button.onClick();
                    }
                }
            }
        }

        timer++;
        if (timer >= gameSpeed) {
            moveMaterials();
            timer = 0;
        }

        setMousePosition();

        cleanWindow();

        drawMaterials();
        drawGrid({50, 50, 50, 255});
        drawButtons();

        presentWindow();
    }
}