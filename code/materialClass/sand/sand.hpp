#ifndef SAND_APP
#define SAND_APP

#include "../material.hpp"
#include <SDL3/SDL.h>

class Sand : public Material {
    public:

    Sand(Point position);
    void Move() override;
    std::unique_ptr<Material> clone() const override;
};

#endif