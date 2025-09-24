#include "sand.hpp"

Sand::Sand(Point position) : Material(position, {255, 128, 30, 255}, "sand") {}

void Sand::Move() {
    std::array<std::string, 8> neighbors = getNeighbors();
    if (neighbors[6] == "") {
        position.y += 1;
    } else if (neighbors[5] == "") {
        position.y += 1;
        position.x -= 1;
    } else if (neighbors[7] == "") {
        position.y += 1;
        position.x += 1;
    } else if (neighbors[6] == "water") {
        position.y += 1;
    }
}

std::unique_ptr<Material> Sand::clone() const {
    return std::make_unique<Sand>(*this);
}