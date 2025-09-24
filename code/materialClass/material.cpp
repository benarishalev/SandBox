#include "material.hpp"
#include "../GLOBALS/global.hpp"

Material::Material(Point position, SDL_Color color, std::string type) {
    this->position = position;
    this->color = color;
    this->type = type;
}

Material::Material() {
    this->type = "";
}

void Material::Draw() {
    Global::drawRect(this->color, position.x * Global::GRID_SIZE, position.y * Global::GRID_SIZE, Global::GRID_SIZE, Global::GRID_SIZE, true);
}

std::array<std::string, 8> Material::getNeighbors() {
    std::array<std::string, 8> neighbors;
    
    const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int i = 0; i < 8; i++) {
        int nx = position.x + dx[i];
        int ny = position.y + dy[i];

        if (nx < 0 || nx >= Global::gridDimenstion.x || ny < 0 || ny >= Global::gridDimenstion.y) {
            neighbors[i] = "void";
        } else {
            neighbors[i] = Global::materialGrid[ny][nx];
        }
    }
    return neighbors;
}

void Material::Move() {}