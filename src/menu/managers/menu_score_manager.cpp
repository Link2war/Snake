#include "../../../include/menu/managers/menu_score_manager.h"


MenuScoreManager::MenuScoreManager(ScoreData* data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal) :
    m_data(data),
    m_lastScoreBox(0, "score : ", glyphSize, fontPath, posLast),
    m_bestScoreBox(0, "record : ", glyphSize, fontPath, posBest),
    m_totalScoreBox(0, "score total : ", glyphSize, fontPath, posTotal)
{

}

void MenuScoreManager::refreshFromData()
{
    m_lastScoreBox.setValue(m_data->getLastScore());
    m_bestScoreBox.setValue(m_data->getBestScore());
    m_totalScoreBox.setValue(m_data->getTotalScore());
}

void MenuScoreManager::Draw(GLint* renderUniform) const
{
    m_lastScoreBox.Draw(renderUniform);
    m_bestScoreBox.Draw(renderUniform);
    m_totalScoreBox.Draw(renderUniform);
}

void MenuScoreManager::moveTo(Vector2f velocity, float deltaTime)
{
    Vector2f pos = m_lastScoreBox.getPosition();
    m_lastScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

     pos = m_bestScoreBox.getPosition();
    m_bestScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

    pos = m_totalScoreBox.getPosition();
    m_totalScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));
}