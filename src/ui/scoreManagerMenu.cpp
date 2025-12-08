#include "../../include/ui/scoreManagerMenu.h"


ScoreManagerMenu::ScoreManagerMenu(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal) :
    data(_data),
    lastScoreBox(0, "score : ", glyphSize, fontPath, posLast),
    bestScoreBox(0, "record : ", glyphSize, fontPath, posBest),
    totalScoreBox(0, "score total : ", glyphSize, fontPath, posTotal)
{

}

void ScoreManagerMenu::refreshFromData()
{
    lastScoreBox.setValue(data->getGameplayScore());
    bestScoreBox.setValue(data->getBestScore());
    totalScoreBox.setValue(data->getTotalScore());
}

void ScoreManagerMenu::Draw(GLint* renderUniform) const
{
    lastScoreBox.Draw(renderUniform);
    bestScoreBox.Draw(renderUniform);
    totalScoreBox.Draw(renderUniform);
}

void ScoreManagerMenu::moveTo(Vector2f velocity, float deltaTime)
{
    Vector2f pos = lastScoreBox.getPosition();
    lastScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

     pos = bestScoreBox.getPosition();
    bestScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));

    pos = totalScoreBox.getPosition();
    totalScoreBox.setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));
}