#include "../../../include/gameplay/items/game_item.h"


GameItem::GameItem(Texture& texture, Vector2f position) :
    m_sprite(texture, position),
    m_initPosition(position)
{
    Vector2f size = m_sprite.getSize();
    m_sprite.setOrigin(size.x/2, size.y/2);
}

void GameItem::Draw(GLint* renderUniform) const
{
    m_sprite.Draw(renderUniform);
}

void GameItem::setPosition(Vector2f boardPos, float cellSize)
{
    Vector2f origin = m_sprite.getOrigin();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribCellPos(0, 15);
    int x = distribCellPos(gen) * cellSize + boardPos.x + origin.x;
    int y = distribCellPos(gen) * cellSize + boardPos.y + origin.y;

    m_sprite.setPosition(x, y);
}

void GameItem::reset()
{
    m_sprite.setPosition(m_initPosition);
}

Vector2f GameItem::getPosition() const
{
    return m_sprite.getPosition();
}