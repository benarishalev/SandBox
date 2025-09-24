#ifndef BUTTON_APP
#define BUTTON_APP

#include "../pointClass/point.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <algorithm>
#include <cstdint>

class Button {
    public:
        std::string type;
        Point position;
        Point size;
        SDL_Color color;
        SDL_Color hoverColor;
    
    Button(Point position, Point size, SDL_Color color, SDL_Color hoverColor, std::string type);
    Button(Point position, Point size, SDL_Color color, std::string type);
    Button();
    void Draw();
    SDL_Color getColor();
    bool isHover();
    void onClick();
};

#endif