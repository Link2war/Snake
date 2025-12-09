#pragma once

#include <BBOP/Graphics.h>


class GameBoard : public BbopDrawable
{
private :
    Sprite m_sprite;
    float m_cellSize;

public :
    GameBoard(Texture& texture, float cellSize);
    virtual ~GameBoard() = default;

    virtual void Draw(GLint* renderUniform) const override;

    Vector2f getPosition() const;
    float getCellSize() const;
};