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
    std::array<Point, 8> points = {
        Point(position.x - 1, position.y - 1),
        Point(position.x, position.y - 1),
        Point(position.x + 1, position.y - 1),
        Point(position.x - 1, position.y),
        Point(position.x + 1, position.y),
        Point(position.x - 1, position.y + 1),
        Point(position.x, position.y + 1),
        Point(position.x + 1, position.y + 1)
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < Global::materials.size(); j++) {
            if (Global::materials[j]->position == points[i]) {
                neighbors[i] = Global::materials[j]->type;
            }
        }
        if (points[i].x < 0 || points[i].x >= Global::WIDTH/Global::GRID_SIZE || points[i].y < 0 || points[i].y >= Global::HEIGHT/Global::GRID_SIZE) {
            neighbors[i] = "void";
        }
    }
    return neighbors;
}

void Material::Move() {}