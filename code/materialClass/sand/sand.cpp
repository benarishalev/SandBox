#include "sand.hpp"

#include "../../GLOBALS/global.hpp"

Sand::Sand(Point position) : Material(position, {255, 128, 30, 255}, "sand") {}

void Sand::Move() {
    std::array<Material*, 8> neighbors = getNeighbors();
    if (neighbors[6]->type == "null") {
        position.y += 1;
    } else if (neighbors[5]->type == "null") {
        position.y += 1;
        position.x -= 1;
    } else if (neighbors[7]->type == "null") {
        position.y += 1;
        position.x += 1;
    }

    if (neighbors[6]->type == "water") {
        position.y += 1;
        neighbors[6]->position.y -= 1;
        Global::updateGrid();
    } else if (neighbors[5]->type == "water") {
        position.y += 1;
        position.x -= 1;
        neighbors[5]->position.y -= 1;
        neighbors[5]->position.x += 1;
        Global::updateGrid();
    } else if (neighbors[7]->type == "water") {
        position.y += 1;
        position.x += 1;
        neighbors[7]->position.y -= 1;
        neighbors[7]->position.x -= 1;
        Global::updateGrid();
    }
}

std::unique_ptr<Material> Sand::clone() const {
    return std::make_unique<Sand>(*this);
}