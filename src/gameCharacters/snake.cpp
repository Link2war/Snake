#include "../../include/gameCharacters/snake.h"


Snake::Snake(Vector2f position) : 
    segments(),
    initPosition(position)
{
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
    segments.push_back(SnakeSegment("assets/sprites/snake/0.png", initPosition));
    segments.push_back(SnakeSegment("assets/sprites/snake/1.png", Vector2f(initPosition.x-32, initPosition.y)));
    segments.push_back(SnakeSegment("assets/sprites/snake/2.png", Vector2f(initPosition.x-64, initPosition.y)));
}

void Snake::reset()
{
    segments.clear();
    segments.shrink_to_fit();

    initBody();
}

void Snake::Draw(GLint* renderUniform) const
{
    for (auto SnakeSegment : segments)
    {
        SnakeSegment.Draw(renderUniform);
    }
}

void Snake::update(Vector2i inputDirection)
{
    if (segments.front().onCell()) {
        updateFrontDirection(inputDirection);
    }
    
    updateBody();
}

void Snake::updateFrontDirection(Vector2i inputDirection)
{
    Vector2i direction = segments.front().getDirection();   
    Vector2i newDirection = direction;

    // vérifie si la direction n'est pas opposée
    if ((inputDirection.x == 0 && inputDirection.y != -direction.y) || (inputDirection.y == 0 && inputDirection.x != -direction.x)) {
        newDirection = inputDirection;
    }
    segments.front().setDirection(newDirection);
}

void Snake::updateBody()
{
    segments.front().update();

    Vector2i direction = segments.front().getDirection();

    for (long unsigned int i=1; i<=segments.size()-1; i++)
    {
        // met à jour la direction des SnakeSegments si le snake est en mouvement (dépend de la tête du snake)
        if (segments[i].onCell() && (direction.x != 0 || direction.y !=0)) 
        {
            Vector2f nextPos = segments[i-1].getStartPosition(); 
            Vector2f currentPos = segments[i].getCurrentPosition();
            Vector2i newDirection = Vector2i(0, 0);

            if (nextPos.y < currentPos.y) newDirection.y = -1;
            else if (nextPos.y > currentPos.y) newDirection.y = 1;
            else if (nextPos.x < currentPos.x) newDirection.x = -1;
            else if (nextPos.x > currentPos.x) newDirection.x = 1;

            segments[i].setDirection(newDirection);
        }

        // met à jour la position des SnakeSegments et de leur Sprite
        segments[i].update();
    }
}

void Snake::addSegment()
{
    // modifie le Sprite de queue en Sprite de corps
    segments.back().setSprite("assets/sprites/snake/1.png");

    // Génère un SnakeSegment avec le Sprite de queue
    SnakeSegment tail("assets/sprites/snake/2.png", segments.back().getStartPosition());
    segments.push_back(tail);
}

bool Snake::isOutOfBounds(float offsetX, float offsetY)
{   
    Vector2f pos = segments.front().getCurrentPosition();
    return (pos.x -16 < offsetX || pos.x -16 > offsetX+512-32 || pos.y -16 < offsetY || pos.y -16 > offsetY+512-32);
}

bool Snake::isBittingBody()
{
    for(long unsigned int i=1; i<=segments.size()-1; i++)
    {
        Vector2f headPos = segments.front().getCurrentPosition();
        Vector2f segmentsPos = segments[i].getStartPosition();

        if (headPos.x == segmentsPos.x && headPos.y == segmentsPos.y) {
            return true;
        }
    }
    return false;
}

bool Snake::collideFruit(Vector2f fruitPosition)
{
    for (auto SnakeSegment : segments)
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