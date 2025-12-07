#include "../../include/ui/scoreManagerGameplay.h"


ScoreManagerGameplay::ScoreManagerGameplay(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f position) :
    data(_data),
    scoreBox(0, "score : ", glyphSize, fontPath, position)
{

}

void ScoreManagerGameplay::refreshFromData()
{
    scoreBox.setValue(data->getGameplayScore());
}

void ScoreManagerGameplay::Draw(GLint* renderUniform) const
{
    scoreBox.Draw(renderUniform);
}