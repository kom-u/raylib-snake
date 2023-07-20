#include "Audio.hpp"

Audio::Audio()
{
    eatSfx = LoadSound((Asset::audioPath + "eat.mp3").c_str());
    gameOverSfx = LoadSound((Asset::audioPath + "wall.mp3").c_str());
}

Audio::~Audio()
{
    UnloadSound(eatSfx);
    UnloadSound(gameOverSfx);
}