#include "../../../include/menu/managers/menuTimeManager.h"


MenuTimeManager::MenuTimeManager(TimeData* _data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal) :
    data(_data),
    timeBox(0, "temps : ", glyphSize, fontPath, posLast),
    bestTimeBox(0, "meilleur temps : ", glyphSize, fontPath, posBest)
{

}

void MenuTimeManager::refreshFromData()
{
    timeBox.setValue(data->getGameplayTime());
    bestTimeBox.setValue(data->getBestTime());
    //totalTimeBox.setValue(data->getTotalScore());
}

void MenuTimeManager::Draw(GLint* renderUniform) const
{
    timeBox.Draw(renderUniform);
    bestTimeBox.Draw(renderUniform);
    //totalTimeBox.Draw(renderUniform);
}

void MenuTimeManager::moveTo(Vector2f velocity, float deltaTime)
{
    Vector2f pos = timeBox.getPosition();
    timeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

     pos = bestTimeBox.getPosition();
    bestTimeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

    //pos = totalTimeBox.getPosition();
    //totalTimeBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));
}