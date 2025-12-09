#pragma once

#include <BBOP/Graphics.h>
#include "../../data/score_data.h"
#include "../../ui/score_box.h"

class MenuScoreManager : public BbopDrawable
{
private :
    ScoreData* m_data; // ne lui appartient pas
    ScoreBox m_lastScoreBox;
    ScoreBox m_bestScoreBox;
    ScoreBox m_totalScoreBox;

public :
    MenuScoreManager(ScoreData* data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal);

    virtual ~MenuScoreManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;

    void moveTo(Vector2f velocity, float deltaTime);
};
