#include "point.hpp"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

bool Point::operator==(const Point& other) {
    if (this->x == other.x && this->y == other.y) {
        return true;
    }
    return false;
}