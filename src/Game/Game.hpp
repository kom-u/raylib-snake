#pragma once
#include "../lib.hpp"

using namespace std;

class Game
{
public:
    Audio audio;

    bool isRunning;
    int score;

    Snake snake;
    Food food{snake.body};

    Game();
    ~Game();

    void Draw();
    void Update();

    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithBody();

    void GameOver();

    void HandleInput();
};