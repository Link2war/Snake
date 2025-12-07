#include "../../include/gameCharacters/block.h"


Block::Block(Texture texture, Vector2f position) :
    sprite(Sprite(texture)),
    speed(4),
    direction(Vector2i(0, 0)),
    startPosition(position),
    currentPosition(position),
    targetPosition(position)
{
    sprite.setPosition(currentPosition);
    Vector2f size = sprite.getSize();
    sprite.setOrigin(size.x/2, size.y/2);
}

Block::~Block()
{
    // std::cout << "block du serpent supprimé" << std::endl;
}

void Block::Draw(GLint* renderUniform) const
{
    sprite.Draw(renderUniform);
}

void Block::update()
{
    updateCurrentPosition();
    sprite.setPosition(currentPosition.x, currentPosition.y);

    if (onCell()) {
        updateStartPosition();
        updateTargetPosition();
    }    
}

void Block::updateRotation()
{
    if (direction.x == -1 && sprite.getRotation() != 3.14) {
        sprite.setRotation(3.14);
    }
    if (direction.x == 1 && sprite.getRotation() != 0) {
        sprite.setRotation(0);
    }
    if (direction.y == -1 && sprite.getRotation() != 3*3.14/2) {
        sprite.setRotation(3*3.14/2);
    }
    if (direction.y == 1 && sprite.getRotation() != 3.14/2) {
        sprite.setRotation(3.14/2);
    }
}

void Block::updateCurrentPosition()
{
    if (onCell()) {
        updateRotation();
    }

    Vector2f velocity = Vector2f(speed*direction.x, speed*direction.y);
    currentPosition = Vector2f(currentPosition.x + velocity.x, currentPosition.y + velocity.y);
}

void Block::updateStartPosition()
{
    startPosition = currentPosition;
}

void Block::updateTargetPosition()
{
    Vector2i nextCell = Vector2i(32*direction.x, 32*direction.y);
    targetPosition = Vector2f(targetPosition.x + nextCell.x, targetPosition.y + nextCell.y);
}

void Block::setDirection(Vector2i _direction)
{
    direction = _direction;
}

void Block::setSprite(Texture texture)
{
    sprite.setTexture(texture);
}

bool Block::onCell() const
{
    return (int(currentPosition.x - 16) %32 == 0 && int(currentPosition.y + 8) %32 == 0);
}

Vector2f Block::getStartPosition() const
{
    return startPosition;
}

Vector2f Block::getCurrentPosition() const
{
    return currentPosition;
}

Vector2f Block::getTargetPosition() const
{
    return targetPosition;
}

Vector2i Block::getDirection() const
{
    return direction;
}