#include "Food.hpp"

Food::Food(deque<Vector2> snakeBody)
{
    Image image = LoadImage(TextFormat("%sfood.png", Asset::texturesPath.c_str()));
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    position = GenerateRandomPosition(snakeBody);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    float x = Setting::boardOffset + position.x * Setting::cellSize;
    float y = Setting::boardOffset + position.y * Setting::cellSize;

    DrawTexture(texture, x, y, Setting::white);
}

Vector2 Food::GenerateRandomPosition(deque<Vector2> snakeBody)
{
    float x = GetRandomValue(0, Setting::cellCount - 1), y = GetRandomValue(0, Setting::cellCount - 1);

    for (Vector2 &cell : snakeBody)
    {
        if (!Vector2Equals(Vector2{x, y}, cell))
            continue;
        return GenerateRandomPosition(snakeBody);
    }
    return Vector2{x, y};
}