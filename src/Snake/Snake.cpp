#include "Snake.hpp"

Snake::Snake()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    addSegment = false;
}

void Snake::Draw()
{
    for (Vector2 &cell : body)
    {
        float x = Setting::boardOffset + cell.x * Setting::cellSize;
        float y = Setting::boardOffset + cell.y * Setting::cellSize;

        Rectangle segment = Rectangle{x, y, (float)Setting::cellSize, (float)Setting::cellSize};

        DrawRectangleRounded(segment, 0.5, 6, Setting::darkGreen);
    }
}

void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment == true)
        addSegment = false;
    else
        body.pop_back();
}

void Snake::Reset()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
}