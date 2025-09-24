#ifndef STONE_APP
#define STONE_APP

#include "../material.hpp"
#include <SDL3/SDL.h>

class Stone : public Material {
    public:

    Stone(Point position);
    void Move() override;
    std::unique_ptr<Material> clone() const override;
};

#endif