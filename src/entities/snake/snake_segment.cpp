#include "../../../include/entities/snake/snake_segment.h"


std::unique_ptr<Texture> SnakeSegment::m_textures[3];

SnakeSegment::SnakeSegment(BodyPart bodyPart, Vector2f position) :
    m_sprite(*m_textures[int(bodyPart)]),
    m_speed(32/8*60),
    m_direction(Vector2i(0, 0)),
    m_startPosition(position),
    m_currentPosition(position),
    m_targetPosition(position)
{
    m_sprite.setPosition(m_currentPosition);
    Vector2f size = m_sprite.getSize();
    m_sprite.setOrigin(size.x/2, size.y/2);

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
        m_textures[n] = std::make_unique<Texture>((base + std::to_string(n) + ".png").c_str());
    }
}

void SnakeSegment::Draw(GLint* renderUniform) const
{
    m_sprite.Draw(renderUniform);
}

void SnakeSegment::update(float deltaTime)
{
    updateCurrentPosition(deltaTime);
    m_sprite.setPosition(m_currentPosition.x, m_currentPosition.y);

    if (onCell()) {
        updateStartPosition();
        updateTargetPosition();
    }    
}

void SnakeSegment::updateRotation()
{
    if (m_direction.x == -1 && m_sprite.getRotation() != 3.14) {
        m_sprite.setRotation(3.14);
    }
    if (m_direction.x == 1 && m_sprite.getRotation() != 0) {
        m_sprite.setRotation(0);
    }
    if (m_direction.y == -1 && m_sprite.getRotation() != 3*3.14/2) {
        m_sprite.setRotation(3*3.14/2);
    }
    if (m_direction.y == 1 && m_sprite.getRotation() != 3.14/2) {
        m_sprite.setRotation(3.14/2);
    }
}

void SnakeSegment::updateCurrentPosition(float deltaTime)
{
    if (onCell()) {
        updateRotation();
    }

    Vector2f velocity = Vector2f(m_speed*m_direction.x, m_speed*m_direction.y);

    m_currentPosition.x += std::round(velocity.x*deltaTime);
    m_currentPosition.y += std::round(velocity.y*deltaTime);
}

void SnakeSegment::updateStartPosition()
{
    m_startPosition = m_currentPosition;
}

void SnakeSegment::updateTargetPosition()
{
    Vector2i nextCell = Vector2i(32*m_direction.x, 32*m_direction.y);
    m_targetPosition = Vector2f(m_targetPosition.x + nextCell.x, m_targetPosition.y + nextCell.y);
}

void SnakeSegment::setDirection(Vector2i direction)
{
    m_direction = direction;
}

void SnakeSegment::setTexture(BodyPart bodyPart)
{
    m_sprite.setTexture(*m_textures[int(bodyPart)]);
}

bool SnakeSegment::onCell() const
{
    Vector2f origin = m_sprite.getOrigin();
    float rx = std::round(m_currentPosition.x / 32.0f) * 32.0f -origin.x;
    float ry = std::round(m_currentPosition.y / 32.0f) * 32.0f -origin.y+8;

    // vérfie la valeur absolue
    return (std::abs(m_currentPosition.x - rx) < 0.1f && std::abs(m_currentPosition.y - ry) < 0.1f);
}

Vector2f SnakeSegment::getStartPosition() const
{
    return m_startPosition;
}

Vector2f SnakeSegment::getCurrentPosition() const
{
    return m_currentPosition;
}

Vector2f SnakeSegment::getTargetPosition() const
{
    return m_targetPosition;
}

Vector2i SnakeSegment::getDirection() const
{
    return m_direction;
}