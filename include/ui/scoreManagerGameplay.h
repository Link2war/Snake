#pragma once

#include <BBOP/Graphics.h>
#include "../data/scoreData.h"
#include "dataBox.h"

class ScoreManagerGameplay : public BbopDrawable
{
private :
    ScoreData* data; // ne lui appartient pas
    DataBox scoreBox;

public :
    ScoreManagerGameplay(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f position);

    virtual ~ScoreManagerGameplay() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;
};
