#ifndef MATERIAL_APP
#define MATERIAL_APP

#include "../pointClass/point.hpp"
#include <SDL3/SDL.h>
#include <array>
#include <string>

class Material {
    public:
        Point position;
        SDL_Color color;
        std::string type;
    
    Material(Point position, SDL_Color color, std::string type);
    Material();
    void Draw();
    std::array<std::string, 8> getNeighbors();
    virtual void Move();
};

#endif