#pragma once

#include <BBOP/Graphics.h>
#include <random>


class GameItem : public BbopDrawable
{
private :
    Sprite m_sprite;
    Vector2f m_initPosition;

public :
    GameItem(Texture& texture, Vector2f position);
    virtual ~GameItem() = default;

    virtual void Draw(GLint* renderUniform) const override;

    void setPosition(Vector2f boardPos, float cellSize);
    void reset();

    Vector2f getPosition() const;
};