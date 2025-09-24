#include "water.hpp"

Water::Water(Point position) : Material(position, {0, 128, 255, 255}, "water") {}

void Water::Move() {
    std::array<std::string, 8> neighbors = getNeighbors();
    if (neighbors[6] == "") {
        position.y += 1;
    } else if (neighbors[5] == "") {
        position.y += 1;
        position.x -= 1;
    } else if (neighbors[7] == "") {
        position.y += 1;
        position.x += 1;
    } else if (neighbors[3] == "" && neighbors[4] == "") {
        position.x += (rand() % 2 == 0) ? 1 : -1;
    } else if (neighbors[3] == "") {
        position.x -= 1;
    } else if (neighbors[4] == "") {
        position.x += 1;
    } else if (neighbors[1] == "sand") {
        position.y -= 1;
    }
}

std::unique_ptr<Material> Water::clone() const {
    return std::make_unique<Water>(*this);
}