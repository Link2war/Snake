#include "../include/block.h"


Block::Block(float x, float y) :
    sprite(new Sprite("sprite/snake/default.png")),
    vitesse(2),
    position_depart(x, y),
    position_actuelle(x, y),
    position_arrivee(x, y),
    direction("none")
{
    sprite->setPosition(position_actuelle.x, position_actuelle.y);
}

Block::~Block()
{
}

void Block::update()
{
    move();
    sprite->setPosition(position_actuelle.x, position_actuelle.y);
}

bool Block::onCase()
{
    if (int(position_actuelle.x) %32 == 0 && int(position_actuelle.y) %32 == 0) // une case fait 32/32
    {
        return true;
    }
    return false;
}

void Block::moveUp()
{
    position_actuelle.y -= vitesse;
}

void Block::moveDown()
{
    position_actuelle.y += vitesse;
}

void Block::moveLeft()
{
    position_actuelle.x -= vitesse;
}

void Block::moveRight()
{
    position_actuelle.x += vitesse;
}

void Block::move()
{
    if (direction == "up") moveUp();
    else if (direction == "down") moveDown();
    else if (direction == "left") moveLeft();
    else if (direction == "right") moveRight();
}

void Block::setDirection(Block * block_tete)
{
    if (onCase() || block_tete == nullptr)
    {
        if(position_depart.x > position_arrivee.x) direction = "left";
        else if(position_depart.x < position_arrivee.x) direction = "right";
        else if(position_depart.y > position_arrivee.y) direction = "up";
        else if(position_depart.y < position_arrivee.y) direction = "down";
    }
    else
    {
        if (position_actuelle.x > block_tete->getPositionDepart().x)direction = "left";
        else if (position_actuelle.x < block_tete->getPositionDepart().x)direction = "right";
        else if (position_actuelle.y > block_tete->getPositionDepart().y)direction = "up";
        else if (position_actuelle.y < block_tete->getPositionDepart().y)direction = "down";
    }
}

void Block::setPositionTete(std::string direction_)
{
    if (direction_ == "up") position_arrivee.y = position_depart.y -32;
    if (direction_ == "down") position_arrivee.y = position_depart.y +32;
    if (direction_ == "left") position_arrivee.x = position_depart.x -32;
    if (direction_ == "right") position_arrivee.x = position_depart.x +32;
}

void Block::setPositionDepart(Vector2f position)
{
    position_depart = position;
}

void Block::setPositionActuelle(Vector2f position)
{
    position_actuelle = position;
}

void Block::setPositionArrivee(Vector2f position)
{
    position_arrivee = position;
}

Vector2f Block::getPositionDepart()
{
    return position_depart;
}

Vector2f Block::getPositionActuelle()
{
    return position_actuelle;
}

Vector2f Block::getPositionArrivee()
{
    return position_arrivee;
}

Sprite * Block::getSprite()
{
    return sprite;
}

std::string Block::getDirection()
{
    return direction;
}