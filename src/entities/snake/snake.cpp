#include "../../../include/entities/snake/snake.h"


Snake::Snake(GameBoard& board, Vector2f cellPosition) : 
    m_segments(),
    m_initPosition(Vector2f(0.f, 0.f))
{
    // sprite offset = 16
    m_initPosition.x = board.getPosition().x + cellPosition.x*board.getCellSize() - 16;
    m_initPosition.y = board.getPosition().y + cellPosition.y*board.getCellSize() - 16;

    SnakeSegment::initTextures();
    initBody();

    std::cout << "Snake initialisé" << std::endl;
}

Snake::~Snake()
{
    std::cout << "Snake suprimé" << std::endl;
}

void Snake::initBody()
{
    // génère un SnakeSegment pour chaque partie du corps
    m_segments.push_back(SnakeSegment(BodyPart::Head, m_initPosition));
    m_segments.push_back(SnakeSegment(BodyPart::Body, Vector2f(m_initPosition.x-32, m_initPosition.y)));
    m_segments.push_back(SnakeSegment(BodyPart::Tail, Vector2f(m_initPosition.x-64, m_initPosition.y)));
}

void Snake::reset()
{
    m_segments.clear();
    m_segments.shrink_to_fit();

    initBody();
}

void Snake::Draw(GLint* renderUniform) const
{
    for (auto SnakeSegment : m_segments)
    {
        SnakeSegment.Draw(renderUniform);
    }
}

void Snake::update(Vector2i inputDirection, float deltaTime)
{
    if (m_segments.front().onCell()) {
        updateFrontDirection(inputDirection);
    }
    
    updateBody(deltaTime);
}

void Snake::updateFrontDirection(Vector2i inputDirection)
{
    Vector2i direction = m_segments.front().getDirection();   
    Vector2i newDirection = direction;

    // vérifie si la direction n'est pas opposée
    if ((inputDirection.x == 0 && inputDirection.y != -direction.y) || (inputDirection.y == 0 && inputDirection.x != -direction.x)) {
        newDirection = inputDirection;
    }
    m_segments.front().setDirection(newDirection);
}

void Snake::updateBody(float deltaTime)
{
    m_segments.front().update(deltaTime);

    Vector2i direction = m_segments.front().getDirection();

    for (long unsigned int i=1; i<=m_segments.size()-1; i++)
    {
        // met à jour la direction des Snakem_segmentsSegments si le snake est en mouvement (dépend de la tête du snake)
        if (m_segments[i].onCell() && (direction.x != 0 || direction.y !=0)) 
        {
            Vector2f nextPos = m_segments[i-1].getStartPosition(); 
            Vector2f currentPos = m_segments[i].getCurrentPosition();
            Vector2i newDirection = Vector2i(0, 0);

            if (nextPos.y < currentPos.y) newDirection.y = -1;
            else if (nextPos.y > currentPos.y) newDirection.y = 1;
            else if (nextPos.x < currentPos.x) newDirection.x = -1;
            else if (nextPos.x > currentPos.x) newDirection.x = 1;

            m_segments[i].setDirection(newDirection);
        }

        // met à jour la position des Snakem_segmentsSegments et de leur Sprite
        m_segments[i].update(deltaTime);
    }
}

void Snake::addSegment()
{
    // modifie le Sprite de queue en Sprite de corps
    m_segments.back().setTexture(BodyPart::Body);

    // Génère un SnakeSegment avec le Sprite de queue
    SnakeSegment tail(BodyPart::Tail, m_segments.back().getStartPosition());
    m_segments.push_back(tail);
}

bool Snake::isOutOfBounds(float offsetX, float offsetY)
{   
    Vector2f pos = m_segments.front().getCurrentPosition();
    return (pos.x -16 < offsetX || pos.x -16 > offsetX+512-32 || pos.y -16 < offsetY || pos.y -16 > offsetY+512-32);
}

bool Snake::isBittingBody()
{
    for(long unsigned int i=3; i<=m_segments.size()-1; i++)
    {
        Vector2f headPos = m_segments.front().getTargetPosition();
        Vector2f segmentsPos = m_segments[i].getStartPosition();

        if (headPos.x == segmentsPos.x && headPos.y == segmentsPos.y) {
            return true;
        }
    }
    return false;
}

bool Snake::collideFruit(Vector2f fruitPosition)
{
    for (auto SnakeSegment : m_segments)
    {
        Vector2f startPos = SnakeSegment.getStartPosition();
        if (startPos.x == fruitPosition.x && startPos.y == fruitPosition.y) {
            return true;
        }
    }
    return false;
}

bool Snake::isDead(float offsetX, float offsetY)
{
    return (isOutOfBounds(offsetX, offsetY) || isBittingBody());
}