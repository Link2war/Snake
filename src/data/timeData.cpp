#include "../../include/data/timeData.h"

TimeData::TimeData() :
    time(0.f),
    bestTime(0.f)
{

}

void TimeData::reset()
{
    time = 0.f;
    bestTime = 0.f;
}

void TimeData::setGameplayTime(float _time)
{
    time = _time;
}

void TimeData::updateBestTime()
{
    if (time > bestTime) {
        bestTime = time;
    }
}

float TimeData::getGameplayTime() const
{
    return time;
}

float TimeData::getBestTime() const
{
    return bestTime;
}