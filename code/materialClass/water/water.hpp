#ifndef WATER_APP
#define WATER_APP

#include "../material.hpp"
#include <SDL3/SDL.h>

class Water : public Material {
    public:

    Water(Point position);
    void Move() override;
    std::unique_ptr<Material> clone() const override;
};

#endif