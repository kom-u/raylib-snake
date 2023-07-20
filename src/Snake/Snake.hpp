#pragma once
#include "../lib.hpp"

using namespace std;

class Snake
{
public:
    deque<Vector2> body;
    Vector2 direction;
    bool addSegment;

    Snake();

    void Draw();
    void Update();
    void Reset();
};