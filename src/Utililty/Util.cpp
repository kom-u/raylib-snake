#include "Util.hpp"

double Util::lastUpdateTime = 0;

bool Util::Delay(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
