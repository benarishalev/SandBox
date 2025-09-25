#ifndef METAL_APP
#define METAL_APP

#include "../material.hpp"
#include <SDL3/SDL.h>

class Metal : public Material {
    public:

    Metal(Point position);
    void Move() override;
    std::unique_ptr<Material> clone() const override;
};

#endif