#include "stone.hpp"

Stone::Stone(Point position) : Material(position, {100, 100, 100, 255}, "stone") {}

void Stone::Move() {
    std::array<Material*, 8> neighbors = getNeighbors();
    if (neighbors[6]->type == "null") {
        position.y += 1;
    }
}

std::unique_ptr<Material> Stone::clone() const {
    return std::make_unique<Stone>(*this);
}