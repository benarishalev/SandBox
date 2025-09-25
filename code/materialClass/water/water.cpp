#include "water.hpp"

Water::Water(Point position) : Material(position, {0, 128, 255, 255}, "water") {}

void Water::Move() {
    std::array<Material*, 8> neighbors = getNeighbors();

    if (neighbors[6]->type == "null") {
        position.y += 1;
    } else if (neighbors[6]->type == "null" && neighbors[5]->type == "null") {
        position.y += 1;
        position.x -= 1;
    } else if (neighbors[6]->type == "null" && neighbors[7]->type == "null") {
        position.y += 1;
        position.x += 1;
    } else if (neighbors[3]->type == "null" && neighbors[4]->type == "null") {
        position.x += (rand() % 2 == 0) ? 1 : -1;
    } else if (neighbors[3]->type == "null") {
        position.x -= 1;
    } else if (neighbors[4]->type == "null") {
        position.x += 1;
    }
}

std::unique_ptr<Material> Water::clone() const {
    return std::make_unique<Water>(*this);
}