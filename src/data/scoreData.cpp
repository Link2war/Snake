#include "../../include/data/scoreData.h"

ScoreData::ScoreData() :
    score(0),
    bestScore(0),
    totalScore(0)
{

}

void ScoreData::reset()
{
    score = 0;
    bestScore = 0;
    totalScore = 0;
}

void ScoreData::setGameplayScore(int _score)
{
    score = _score;
}

void ScoreData::updateBestScore()
{
    if (score > bestScore) {
        bestScore = score;
    }
}

void ScoreData::updateTotalScore()
{
    totalScore += score;
}

int ScoreData::getGameplayScore() const
{
    return score;
}

int ScoreData::getBestScore() const
{
    return bestScore;
}

int ScoreData::getTotalScore() const
{
    return totalScore;
}