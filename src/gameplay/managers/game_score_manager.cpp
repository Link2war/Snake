#include "../../../include/gameplay/managers/game_score_manager.h"


GameScoreManager::GameScoreManager(ScoreData* data, int glyphSize, const char* fontPath, Vector2f position) :
    m_data(data),
    m_scoreBox(0, "score : ", glyphSize, fontPath, position)
{

}

void GameScoreManager::refreshFromData()
{
    m_scoreBox.setValue(m_data->getLastScore());
}

void GameScoreManager::Draw(GLint* renderUniform) const
{
    m_scoreBox.Draw(renderUniform);
}