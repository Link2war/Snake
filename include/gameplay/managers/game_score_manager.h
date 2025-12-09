#pragma once

#include <BBOP/Graphics.h>
#include "../../data/score_data.h"
#include "../../ui/score_box.h"

class GameScoreManager : public BbopDrawable
{
private :
    ScoreData* m_data; // ne lui appartient pas
    ScoreBox m_scoreBox;

public :
    GameScoreManager(ScoreData* data, int glyphSize, const char* fontPath, Vector2f position);

    virtual ~GameScoreManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;
};
