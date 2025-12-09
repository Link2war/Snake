#include "../../../include/gameplay/managers/gameTimeManager.h"


GameTimeManager::GameTimeManager(TimeData* _data, int glyphSize, const char* fontPath, Vector2f position) :
    data(_data),
    timeBox(0.f, "temps : ", glyphSize, fontPath, position)
{

}

void GameTimeManager::refreshFromData()
{
    timeBox.setValue(data->getGameplayTime());
}

void GameTimeManager::Draw(GLint* renderUniform) const
{
    timeBox.Draw(renderUniform);
}