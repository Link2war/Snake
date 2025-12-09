#include "../../../include/gameplay/managers/gameScoreManager.h"


GameScoreManager::GameScoreManager(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f position) :
    data(_data),
    scoreBox(0, "score : ", glyphSize, fontPath, position)
{

}

void GameScoreManager::refreshFromData()
{
    scoreBox.setValue(data->getGameplayScore());
}

void GameScoreManager::Draw(GLint* renderUniform) const
{
    scoreBox.Draw(renderUniform);
}