#pragma once

#include <BBOP/Graphics.h>
#include "../../data/timeData.h"
#include "../../ui/dataBox.h"

class MenuTimeManager : public BbopDrawable
{
private :
    TimeData* data; // ne lui appartient pas
    DataBox timeBox;
    DataBox bestTimeBox;
    //DataBox totalScoreBox;

public :
    MenuTimeManager(TimeData* _data, int glyphSize, const char* fontPath, Vector2f posLast, Vector2f posBest, Vector2f posTotal);

    virtual ~MenuTimeManager() = default;

    void refreshFromData();

    virtual void Draw(GLint* renderUniform) const override;

    void moveTo(Vector2f velocity, float deltaTime);
};
