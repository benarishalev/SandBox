#include "GLOBALS/global.hpp"

int main() {
    Global::init(1200, 1200);
    Global::runLoop();
    return 0;
}