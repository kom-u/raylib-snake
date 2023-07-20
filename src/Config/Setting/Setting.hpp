#pragma once
#include "../../lib.hpp"

using namespace std;

class Setting
{
public:
    static bool allowMove;

    static Color green;
    static Color darkGreen;
    static Color white;

    static int cellSize;
    static int cellCount;
    static int boardOffset;

    static int windowWidth;
    static int windowHeight;
};