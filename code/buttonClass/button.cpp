#include "button.hpp"

#include "../GLOBALS/global.hpp"

Button::Button(Point position, Point size, SDL_Color color, SDL_Color hoverColor, std::string type) {
    this->position = position;
    this->size = size;
    this->color = color;
    this->hoverColor = hoverColor;
    this->type = type;
}

Button::Button(Point position, Point size, SDL_Color color, std::string type) {
    this->position = position;
    this->size = size;
    this->color = color;
    this->hoverColor = {Global::getColorValue(color.r, -50), Global::getColorValue(color.g, -50), Global::getColorValue(color.b, -50), 255};
    this->type = type;
}

Button::Button() : Button(Point(0,0), Point(0,0), SDL_Color{0,0,0,0}, SDL_Color{255,255,255,255}, "") {}

void Button::Draw() {
    Global::drawRect(this->getColor(), position.x, position.y, size.x, size.y, true);
    Global::drawRect((Global::currentMaterial == this->type) ? SDL_Color{255, 255, 255, 255} : SDL_Color{0, 0, 0, 255}, position.x, position.y, size.x, size.y, false);
}

SDL_Color Button::getColor() {
    return this->isHover() ? this->hoverColor : this->color;
}

bool Button::isHover() {
    return (Global::mousePosition.x > position.x &&
            Global::mousePosition.x < position.x + size.x &&
            Global::mousePosition.y > position.y &&
            Global::mousePosition.y < position.y + size.y);
}

void Button::onClick() {
    Global::currentMaterial = this->type;
}