#include "../../include/gameCharacters/snakeSegment.h"


std::unique_ptr<Texture> SnakeSegment::textures[3];

SnakeSegment::SnakeSegment(BodyPart bodyPart, Vector2f position) :
    sprite(*textures[int(bodyPart)]),
    speed(4),
    direction(Vector2i(0, 0)),
    startPosition(position),
    currentPosition(position),
    targetPosition(position)
{
    sprite.setPosition(currentPosition);
    Vector2f size = sprite.getSize();
    sprite.setOrigin(size.x/2, size.y/2);

    std::cout << "SnakeSegment initialisé" << std::endl;
}

SnakeSegment::~SnakeSegment()
{
    // std::cout << "SnakeSegment du serpent supprimé" << std::endl;
}

void SnakeSegment::initTextures()
{
    for (int n=0; n<3; n++)
    {
        std::string base = "assets/sprites/snake/";
        textures[n] = std::make_unique<Texture>((base + std::to_string(n) + ".png").c_str());
    }
}

void SnakeSegment::Draw(GLint* renderUniform) const
{
    sprite.Draw(renderUniform);
}

void SnakeSegment::update()
{
    updateCurrentPosition();
    sprite.setPosition(currentPosition.x, currentPosition.y);

    if (onCell()) {
        updateStartPosition();
        updateTargetPosition();
    }    
}

void SnakeSegment::updateRotation()
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

void SnakeSegment::updateCurrentPosition()
{
    if (onCell()) {
        updateRotation();
    }

    Vector2f velocity = Vector2f(speed*direction.x, speed*direction.y);
    currentPosition = Vector2f(currentPosition.x + velocity.x, currentPosition.y + velocity.y);
}

void SnakeSegment::updateStartPosition()
{
    startPosition = currentPosition;
}

void SnakeSegment::updateTargetPosition()
{
    Vector2i nextCell = Vector2i(32*direction.x, 32*direction.y);
    targetPosition = Vector2f(targetPosition.x + nextCell.x, targetPosition.y + nextCell.y);
}

void SnakeSegment::setDirection(Vector2i _direction)
{
    direction = _direction;
}

void SnakeSegment::setTexture(BodyPart bodyPart)
{
    sprite.setTexture(*textures[int(bodyPart)]);
}

bool SnakeSegment::onCell() const
{
    return (int(currentPosition.x - 16) %32 == 0 && int(currentPosition.y + 8) %32 == 0);
}

Vector2f SnakeSegment::getStartPosition() const
{
    return startPosition;
}

Vector2f SnakeSegment::getCurrentPosition() const
{
    return currentPosition;
}

Vector2f SnakeSegment::getTargetPosition() const
{
    return targetPosition;
}

Vector2i SnakeSegment::getDirection() const
{
    return direction;
}