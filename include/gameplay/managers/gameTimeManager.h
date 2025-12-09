#pragma once

#include <BBOP/Graphics.h>
#include "../../data/timeData.h"
#include "../../ui/dataBox.h"

class GameTimeManager : public BbopDrawable
{
private :
    TimeData* data; // ne lui appartient pas
    DataBox timeBox;

public :
    GameTimeManager(TimeData* _data, int glyphSize, const char* fontPath, Vector2f position);

    virtual ~GameTimeManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;
};
