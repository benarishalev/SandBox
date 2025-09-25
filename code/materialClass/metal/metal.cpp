#include "metal.hpp"

Metal::Metal(Point position) : Material(position, {50, 50, 50, 255}, "metal") {}

void Metal::Move() {}

std::unique_ptr<Material> Metal::clone() const {
    return std::make_unique<Metal>(*this);
}