#pragma once

#include <BBOP/Graphics.h>
#include "../data/scoreData.h"
#include "dataBox.h"

class ScoreManagerMenu : public BbopDrawable
{
private :
    ScoreData* data; // ne lui appartient pas
    DataBox lastScoreBox;
    DataBox bestScoreBox;
    DataBox totalScoreBox;

public :
    ScoreManagerMenu(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal);

    virtual ~ScoreManagerMenu() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;

    void moveTo(Vector2f velocity, float deltaTime);
};
