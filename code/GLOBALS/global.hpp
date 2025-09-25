#ifndef GLOBAL_APP
#define GLOBAL_APP

#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
#include <cstdint>

#include "../materialClass/sand/sand.hpp"
#include "../materialClass/water/water.hpp"
#include "../materialClass/stone/stone.hpp"

#include "../buttonClass/button.hpp"

class Global {
    public:
        static int WIDTH;
        static int HEIGHT;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static std::string mode;

        // all
        static Point mousePosition;

        // gameloop
        static int GRID_SIZE;
        static Point gridDimenstion;
        static int gameSpeed;
        static int spawnSize;
        static std::vector<std::unique_ptr<Material>> materials;
        static std::vector<std::vector<Material*>> materialGrid;
        static Sand voidMaterial;
        static Sand nullMaterial;
        static int timer;
        static std::map<std::string, std::unique_ptr<Material>> prototypeMaterials;
        static std::string currentMaterial;
        static std::vector<Button> buttons;

    static void init(int width, int height);
    static void quit();
    static void cleanWindow();
    static void presentWindow();
    static void runLoop();

    // all
    static void setMousePosition();
    static Uint8 getColorValue(Uint8 value, int change);

    // game loop
    static void runGameLoop();
    static void drawGrid(SDL_Color color);
    static void drawRect(SDL_Color color, float x, float y, float width, float height, bool fill = true);
    static void addMaterialToMouse(int xPos, int yPos);
    static void drawMaterials();
    static void moveMaterials();
    static void drawButtons();
};

#endif