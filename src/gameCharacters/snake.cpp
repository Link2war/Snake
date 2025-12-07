#include "../../include/gameCharacters/snake.h"


Snake::Snake(Vector2f position) : 
    body(),
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
    // génère un block pour chaque partie du corps
    body.push_back(Block("assets/sprites/snake/0.png", initPosition));
    body.push_back(Block("assets/sprites/snake/1.png", Vector2f(initPosition.x-32, initPosition.y)));
    body.push_back(Block("assets/sprites/snake/2.png", Vector2f(initPosition.x-64, initPosition.y)));
}

void Snake::reset()
{
    body.clear();
    body.shrink_to_fit();

    initBody();
}

void Snake::Draw(GLint* renderUniform) const
{
    for (auto block : body)
    {
        block.Draw(renderUniform);
    }
}

void Snake::update(Vector2i inputDirection)
{
    if (body.front().onCell()) {
        updateFrontDirection(inputDirection);
    }
    
    updateBlocksBody();
}

void Snake::updateFrontDirection(Vector2i inputDirection)
{
    Vector2i direction = body.front().getDirection();   
    Vector2i newDirection = direction;

    // vérifie si la direction n'est pas opposée
    if ((inputDirection.x == 0 && inputDirection.y != -direction.y) || (inputDirection.y == 0 && inputDirection.x != -direction.x)) {
        newDirection = inputDirection;
    }
    body.front().setDirection(newDirection);
}

void Snake::updateBlocksBody()
{
    body.front().update();

    Vector2i direction = body.front().getDirection();

    for (long unsigned int i=1; i<=body.size()-1; i++)
    {
        // met à jour la direction des blocks si le snake est en mouvement (dépend de la tête du snake)
        if (body[i].onCell() && (direction.x != 0 || direction.y !=0)) 
        {
            Vector2f nextPos = body[i-1].getStartPosition(); 
            Vector2f currentPos = body[i].getCurrentPosition();
            Vector2i newDirection = Vector2i(0, 0);

            if (nextPos.y < currentPos.y) newDirection.y = -1;
            else if (nextPos.y > currentPos.y) newDirection.y = 1;
            else if (nextPos.x < currentPos.x) newDirection.x = -1;
            else if (nextPos.x > currentPos.x) newDirection.x = 1;

            body[i].setDirection(newDirection);
        }

        // met à jour la position des blocks et de leur Sprite
        body[i].update();
    }
}

void Snake::addBlock()
{
    // modifie le Sprite de queue en Sprite de corps
    body.back().setSprite("assets/sprites/snake/1.png");

    // Génère un Block avec le Sprite de queue
    Block tail("assets/sprites/snake/2.png", body.back().getStartPosition());
    body.push_back(tail);
}

bool Snake::isOutOfBounds(float offsetX, float offsetY)
{   
    Vector2f pos = body.front().getCurrentPosition();
    return (pos.x -16 < offsetX || pos.x -16 > offsetX+512-32 || pos.y -16 < offsetY || pos.y -16 > offsetY+512-32);
}

bool Snake::isBittingBody()
{
    for(long unsigned int i=1; i<=body.size()-1; i++)
    {
        Vector2f headPos = body.front().getCurrentPosition();
        Vector2f bodyPos = body[i].getStartPosition();

        if (headPos.x == bodyPos.x && headPos.y == bodyPos.y) {
            return true;
        }
    }
    return false;
}

bool Snake::collideFruit(Vector2f fruitPosition)
{
    for (auto block : body)
    {
        Vector2f startPos = block.getStartPosition();
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