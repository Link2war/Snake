#pragma once

#include <GLFW/glfw3.h>

class Timer
{
private:
    double _startTime;

public:
    Timer();

    void reset();
    double elapsed() const;
};