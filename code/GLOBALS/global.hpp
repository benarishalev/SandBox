#ifndef GLOBAL_APP
#define GLOBAL_APP

#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <memory>

#include "../materialClass/sand.hpp"
#include "../materialClass/water.hpp"

class Global {
    public:
        static int WIDTH;
        static int HEIGHT;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static std::string mode;

        // gameloop
        static int GRID_SIZE;
        static std::vector<std::unique_ptr<Material>> materials;

    static void init(int width, int height);
    static void quit();
    static void cleanWindow();
    static void presentWindow();
    static void runLoop();

    // game loop
    static void runGameLoop();
    static void drawGrid(SDL_Color color);
    static void drawRect(SDL_Color color, float x, float y, float width, float height, bool fill = true);
    static void addMaterialToMouse(int xPos, int yPos, int size);
    static void drawMaterials();
    static void moveMaterials();
};

#endif