#include "Game.hpp"

Game::Game()
{
    isRunning = true;
    score = 0;

    snake = Snake();
    food = Food(snake.body);

    InitAudioDevice();
}

Game::~Game()
{
    CloseAudioDevice();
}

void Game::Draw()
{
    snake.Draw();
    food.Draw();
}

void Game::Update()
{
    if (!isRunning)
        return;

    snake.Update();

    CheckCollisionWithFood();
    CheckCollisionWithEdges();
    CheckCollisionWithBody();
}

void Game::CheckCollisionWithFood()
{
    Vector2 snakeHead = snake.body[0];
    if (!Vector2Equals(snakeHead, food.position))
        return;

    food.position = food.GenerateRandomPosition(snake.body);
    snake.addSegment = true;
    score++;

    // PlaySound(eatSound);
}

void Game::CheckCollisionWithEdges()
{
    Vector2 snakeHead = snake.body[0];
    if (snakeHead.x < 0 || snakeHead.x >= Setting::cellCount || snakeHead.y < 0 || snakeHead.y >= Setting::cellCount)
    {
        GameOver();
        // PlaySound(wallSound);
    }
}

void Game::CheckCollisionWithBody()
{
    Vector2 snakeHead = snake.body[0];
    for (int i = 1; i < snake.body.size(); i++)
    {
        if (!Vector2Equals(snakeHead, snake.body[i]))
            continue;
        GameOver();
        // PlaySound(wallSound);
    }
}

void Game::GameOver()
{
    isRunning = false;
    score = 0;

    snake.Reset();
    food.GenerateRandomPosition(snake.body);

    // PlaySound(wallSound);
}

void Game::HandleInput()
{
    if (!Setting::allowMove)
        return;

    int keyPressed = GetKeyPressed();

    if (keyPressed == KEY_UP || keyPressed == KEY_DOWN || keyPressed == KEY_LEFT || keyPressed == KEY_RIGHT)
    {
        if (keyPressed == KEY_UP && snake.direction.y != 1)
            snake.direction = {0, -1};
        if (keyPressed == KEY_DOWN && snake.direction.y != -1)
            snake.direction = {0, 1};
        if (keyPressed == KEY_LEFT && snake.direction.x != 1)
            snake.direction = {-1, 0};
        if (keyPressed == KEY_RIGHT && snake.direction.x != -1)
            snake.direction = {1, 0};

        Setting::allowMove = false;
        isRunning = true;
    }
}