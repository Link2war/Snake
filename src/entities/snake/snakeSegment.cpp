#include "../../../include/entities/snake/snakeSegment.h"


std::unique_ptr<Texture> SnakeSegment::textures[3];

SnakeSegment::SnakeSegment(BodyPart bodyPart, Vector2f position) :
    sprite(*textures[int(bodyPart)]),
    speed(32/8*60),
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

void SnakeSegment::update(float deltaTime)
{
    updateCurrentPosition(deltaTime);
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

void SnakeSegment::updateCurrentPosition(float deltaTime)
{
    if (onCell()) {
        updateRotation();
    }

    Vector2f velocity = Vector2f(speed*direction.x, speed*direction.y);

    currentPosition.x += std::round(velocity.x*deltaTime);
    currentPosition.y += std::round(velocity.y*deltaTime);
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
    Vector2f origin = sprite.getOrigin();
    float rx = std::round(currentPosition.x / 32.0f) * 32.0f -origin.x;
    float ry = std::round(currentPosition.y / 32.0f) * 32.0f -origin.y+8;

    // vérfie la valeur absolue
    return (std::abs(currentPosition.x - rx) < 0.1f && std::abs(currentPosition.y - ry) < 0.1f);
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