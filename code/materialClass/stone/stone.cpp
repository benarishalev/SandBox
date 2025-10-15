#include "stone.hpp"

#include "../../GLOBALS/global.hpp"

Stone::Stone(Point position) : Material(position, {100, 100, 100, 255}, "stone") {}

void Stone::Move() {
    std::array<Material*, 8> neighbors = getNeighbors();
    if (neighbors[6]->type == "null") {
        position.y += 1;
    } else if (neighbors[6]->type == "water") {
        position.y += 1;
        neighbors[6]->position.y -= 1;
        Global::materialGrid[this->position.y][this->position.x] = &Global::nullMaterial;
        Global::materialGrid[neighbors[6]->position.y][neighbors[6]->position.x] = this;
    } else if (neighbors[5]->type == "water") {
        position.y += 1;
        position.x -= 1;
        neighbors[5]->position.y -= 1;
        neighbors[5]->position.x += 1;
        Global::materialGrid[this->position.y][this->position.x] = &Global::nullMaterial;
        Global::materialGrid[neighbors[5]->position.y][neighbors[5]->position.x] = this;
    } else if (neighbors[7]->type == "water") {
        position.y += 1;
        position.x += 1;
        neighbors[7]->position.y -= 1;
        neighbors[7]->position.x -= 1;
        Global::materialGrid[this->position.y][this->position.x] = &Global::nullMaterial;
        Global::materialGrid[neighbors[7]->position.y][neighbors[7]->position.x] = this;
    }
}

std::unique_ptr<Material> Stone::clone() const {
    return std::make_unique<Stone>(*this);
}