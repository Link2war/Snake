#include "../../../include/gameplay/managers/game_time_manager.h"


GameTimeManager::GameTimeManager(TimeData* _data, int glyphSize, const char* fontPath, Vector2f position) :
    m_data(_data),
    m_timeBox("temps : ", glyphSize, fontPath, position)
{

}

void GameTimeManager::refreshFromData()
{
    int seconds = m_data->getLastTime();
    int minutes = 0;
    int hours = 0;
    if (seconds > 60) {
        minutes = seconds/60;
        seconds %= 60;
    }
    if (minutes > 60) {
        hours = minutes/60;
        minutes %= 60;
    }
    m_timeBox.setTime(seconds, minutes, hours);
}

void GameTimeManager::Draw(GLint* renderUniform) const
{
    m_timeBox.Draw(renderUniform);
}