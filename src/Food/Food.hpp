#pragma once
#include "../lib.hpp"

using namespace std;

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody);
    ~Food();

    void Draw();
    Vector2 GenerateRandomPosition(deque<Vector2> snakeBody);
};