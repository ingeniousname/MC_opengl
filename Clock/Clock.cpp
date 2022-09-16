#include "Clock.h"

Clock::Clock() : duration(0)
{
    start = std::chrono::high_resolution_clock::now();
}

void Clock::reset()
{
    start = std::chrono::high_resolution_clock::now();
}

double Clock::getTime()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    return duration.count() * 1000.0f;
}
