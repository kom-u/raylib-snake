#include "Setting.hpp"

bool Setting::allowMove = true;

Color Setting::green = {173, 204, 96, 255};
Color Setting::darkGreen = {43, 51, 24, 255};
Color Setting::white = {255, 255, 255, 255};

int Setting::cellSize = 30;
int Setting::cellCount = 25;
int Setting::boardOffset = 75;

int Setting::windowWidth = 2 * boardOffset + cellSize * cellCount;
int Setting::windowHeight = 2 * boardOffset + cellSize * cellCount;