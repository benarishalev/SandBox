#include "GLOBALS/global.hpp"

int main() {
    Global::init(1500, 1200);
    Global::runLoop();
    return 0;
}