#include "../../../include/menu/managers/menu_time_manager.h"


MenuTimeManager::MenuTimeManager(TimeData* data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal) :
    m_data(data),
    m_timeBox("temps : ", glyphSize, fontPath, posLast),
    m_bestTimeBox("meilleur temps : ", glyphSize, fontPath, posBest)
{

}

void MenuTimeManager::refreshFromData()
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

    int time = m_data->getLastTime();
    if (time > m_data->getBestTime()) {
        seconds = time;
        if (seconds > 60) {
            minutes = seconds/60;
            seconds %= 60;
        }
        if (minutes > 60) {
            hours = minutes/60;
            minutes %= 60;
        }
        m_bestTimeBox.setTime(seconds, minutes, hours);
    }
    //totalm_TimeBox.setValue(data->getTotalScore());
}

void MenuTimeManager::Draw(GLint* renderUniform) const
{
    m_timeBox.Draw(renderUniform);
    m_bestTimeBox.Draw(renderUniform);
    //totalm_TimeBox.Draw(renderUniform);
}

void MenuTimeManager::moveTo(Vector2f velocity, float deltaTime)
{
    Vector2f pos = m_timeBox.getPosition();
    m_timeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

     pos = m_bestTimeBox.getPosition();
    m_bestTimeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

    //pos = totalm_TimeBox.getPosition();
    //totalm_TimeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));
}