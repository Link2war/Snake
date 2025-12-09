#pragma once

#include <BBOP/Graphics.h>
#include "../../data/time_data.h"
#include "../../ui/time_box.h"

class MenuTimeManager : public BbopDrawable
{
private :
    TimeData* m_data; // ne lui appartient pas
    TimeBox m_timeBox;
    TimeBox m_bestTimeBox;

public :
    MenuTimeManager(TimeData* data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal);

    virtual ~MenuTimeManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;

    void moveTo(Vector2f velocity, float deltaTime);
};
