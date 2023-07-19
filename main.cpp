#include <iostream>
#include <deque>
#include <raylib.h>
#include <raymath.h>

using namespace std;

static bool isMoveAllowed = true;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw()
    {
        for (Vector2 &cell : body)
        {
            Rectangle segment = Rectangle{offset + cell.x * cellSize, offset + cell.y * cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment == true)
            addSegment = false;
        else
            body.pop_back();
    }

    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Assets/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);

        position = GenerateRandomPosition(snakeBody);
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPosition(deque<Vector2> snakeBody)
    {
        float x = GetRandomValue(0, cellCount - 1), y = GetRandomValue(0, cellCount - 1);

        for (Vector2 &cell : snakeBody)
        {
            if (Vector2Equals(Vector2{x, y}, cell))
            {
                return GenerateRandomPosition(snakeBody);
            }
        }

        return Vector2{x, y};
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;

    Sound eatSound;
    Sound wallSound;

    Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("Assets/eat.mp3");
        wallSound = LoadSound("Assets/wall.mp3");
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithBody();
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPosition(snake.body);
            snake.addSegment = true;
            score++;
            PlaySound(eatSound);
        }
    }

    void CheckCollisionWithEdges()
    {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1 || snake.body[0].y == cellCount || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void CheckCollisionWithBody()
    {
        deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();

        for (Vector2 &cell : headlessBody)
        {
            if (Vector2Equals(snake.body[0], cell))
            {
                GameOver();
            }
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.GenerateRandomPosition(snake.body);
        running = false;
        score = 0;

        PlaySound(wallSound);
    }

    void HandleInput()
    {
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
        {
            snake.direction = {0, -1};
            running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = {0, 1};
            running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = {-1, 0};
            running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = {1, 0};
            running = true;
        }
    }
};

int main()
{
    cout << "Starting the game..." << endl;

    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Ular Lily Lepas");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (EventTriggered(0.2))
        {
            game.Update();
        }

        game.HandleInput();

        ClearBackground(green);
        DrawText(TextFormat("Score: %i", game.score), offset - 5, 20, 40, darkGreen);
        DrawText("Ular Lily Lepas", offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}