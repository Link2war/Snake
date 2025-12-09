#include "../../include/data/score_data.h"

ScoreData::ScoreData() :
    m_lastScore(0),
    m_bestScore(0),
    m_totalScore(0)
{

}

void ScoreData::reset()
{
    m_lastScore = 0;
    m_bestScore = 0;
    m_totalScore = 0;
}

void ScoreData::setLastScore(int score)
{
    m_lastScore = score;
}

void ScoreData::updateBestScore()
{
    if (m_lastScore > m_bestScore) {
        m_bestScore = m_lastScore;
    }
}

void ScoreData::updateTotalScore()
{
    m_totalScore += m_lastScore;
}

int ScoreData::getLastScore() const
{
    return m_lastScore;
}

int ScoreData::getBestScore() const
{
    return m_bestScore;
}

int ScoreData::getTotalScore() const
{
    return m_totalScore;
}