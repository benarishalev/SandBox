#ifndef GLOBAL_APP
#define GLOBAL_APP

#include <SDL3/SDL.h>
#include <string>

class Global {
    public:
        static int WIDTH;
        static int HEIGHT;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
        static std::string mode;

    static void init(int width, int height);
    static void quit();
    static void cleanWindow();
    static void presentWindow();
    static void runLoop();
    static void runGameLoop();
};

#endif