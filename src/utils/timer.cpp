#include "../../include/utils/timer.h"


Timer::Timer() :
    _startTime(glfwGetTime())
{

}

void Timer::reset()
{
    _startTime = glfwGetTime();
}

double Timer::elapsed() const
{
    return glfwGetTime() - _startTime;
}