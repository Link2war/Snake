#include "../../include/gameplay/game_board.h"


GameBoard::GameBoard(Texture& texture, float cellSize) :
    m_sprite(texture),
    m_cellSize(cellSize)
{
    Vector2f size = m_sprite.getSize();
    m_sprite.setPosition((BBOP_WINDOW_RESOLUTION.x-size.x)/2,(BBOP_WINDOW_RESOLUTION.y-size.y)/2);
}

void GameBoard::Draw(GLint* renderUniform) const
{
    m_sprite.Draw(renderUniform);
}

Vector2f GameBoard::getPosition() const
{
    return m_sprite.getPosition();
}

float GameBoard::getCellSize() const
{
    return m_cellSize;
}