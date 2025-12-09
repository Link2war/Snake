#pragma once

#include <BBOP/Graphics.h>
#include "../../data/scoreData.h"
#include "../../ui/dataBox.h"

class GameScoreManager : public BbopDrawable
{
private :
    ScoreData* data; // ne lui appartient pas
    DataBox scoreBox;

public :
    GameScoreManager(ScoreData* _data, int glyphSize, const char* fontPath, Vector2f position);

    virtual ~GameScoreManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;
};
