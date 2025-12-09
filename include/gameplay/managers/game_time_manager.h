#pragma once

#include <BBOP/Graphics.h>
#include "../../data/time_data.h"
#include "../../ui/time_box.h"

class GameTimeManager : public BbopDrawable
{
private :
    TimeData* m_data; // ne lui appartient pas
    TimeBox m_timeBox;

public :
    GameTimeManager(TimeData* data, int glyphSize, const char* fontPath, Vector2f position);

    virtual ~GameTimeManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;
};
