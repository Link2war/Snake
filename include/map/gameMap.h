#pragma once

#include <BBOP/Graphics.h>
#include "layer.h"


class GameMap : public BbopDrawable
{
private :
    Layer background;
    Layer midground;
    Layer foreground;

public :
    GameMap();
    virtual ~GameMap();

    virtual void Draw(GLint* renderUniform) const override;

    void update(float dt);
};