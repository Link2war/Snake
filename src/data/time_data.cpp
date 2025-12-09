#include "../../include/data/time_data.h"

TimeData::TimeData() :
    m_lastTime(0.f),
    m_bestTime(0.f)
{

}

void TimeData::reset()
{
    m_lastTime = 0.f;
    m_bestTime = 0.f;
}

void TimeData::setLastTime(float _time)
{
    m_lastTime = _time;
}

void TimeData::updateBestTime()
{
    if (m_lastTime > m_bestTime) {
        m_bestTime = m_lastTime;
    }
}

float TimeData::getLastTime() const
{
    return m_lastTime;
}

float TimeData::getBestTime() const
{
    return m_bestTime;
}