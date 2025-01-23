#include "../include/serpent.h"


Block::Block(Texture texture, float x, float y) :
    sprite(new Sprite(texture)),
    vitesse(4),
    direction("none"),
    depart(x, y),
    position(x, y),
    arrivee(x, y),
    suivant(nullptr),
    precedent(nullptr),
    frame(0)
{
    sprite->setPosition(position.x, position.y);
    sprite->setOrigin(16, 16);
}

Block::~Block()
{
}

void Block::update()
{
    setDepart();
    setArrivee();
    setDirection();

    move();

    sprite->setPosition(position.x, position.y);
}

bool Block::onCase()
{
    if (int(position.x - 16) %32 == 0 && int(position.y + 8) %32 == 0) // une case fait 32/32
    {
        return true;
    }
    return false;
}

void Block::moveUp()
{
    position.y -= vitesse;
}

void Block::moveDown()
{
    position.y += vitesse;
}

void Block::moveLeft()
{
    position.x -= vitesse;
}

void Block::moveRight()
{
    position.x += vitesse;
}

void Block::move()
{
    if (direction == "up") 
    {
        if (sprite->getRotation() != 3*3.14/2) sprite->setRotation(3*3.14/2);
        moveUp();
    }
    else if (direction == "down") 
    {
        if (sprite->getRotation() != 3.14/2) sprite->setRotation(3.14/2);
        moveDown();
    }
    else if (direction == "left")
    {
        if (sprite->getRotation() != 3.14) sprite->setRotation(3.14);
        moveLeft();
    }
    else if (direction == "right") 
    {
        if (sprite->getRotation() != 0) sprite->setRotation(0);
        moveRight();
    }
}

void Block::setDirection()
{
    if (onCase() && precedent != nullptr)
    {
        if (position.x > precedent->depart.x) this->direction = "left";
        else if (position.x < precedent->depart.x) this->direction = "right";
        else if (position.y > precedent->depart.y) this->direction = "up";
        else if (position.y < precedent->depart.y) this->direction = "down";
    }
}

void Block::setDepart()
{
    if (onCase()) depart = position;
}

void Block::setArrivee()
{
    if (onCase() && precedent != nullptr) arrivee = precedent->depart;
}

void Block::setSprite(Texture texture)
{
    sprite->setTexture(texture);
}

Vector2f Block::getPosition()
{
    return position;
}

Vector2f Block::getArrivee()
{
    return arrivee;
}

Sprite * Block::getSprite()
{
    return sprite;
}

Block * Block::getSuivant()
{
    return suivant;
}





Serpent::Serpent(float x, float y) : 
    tete(new Block(Texture("sprite/snake/defaut/0.png"), x, y)),
    queue(nullptr)
    
{
    addBlock();
    addBlock();
}

Serpent::~Serpent()
{
    while (tete != nullptr)
    {
        Block* temp = tete;
        tete = tete->suivant;
        delete temp;
    }

    tete = nullptr;
    queue = nullptr;
}

void Serpent::update(std::string direction)
{
    setDirection(direction);
    tete->setDepart();
    setArrivee(); 
    tete->move();
    tete->sprite->setPosition(tete->position.x, tete->position.y);

    Block * block = tete->suivant;
    while(block != nullptr)
    {
        block->update();
        block = block->suivant;
    }  
}

void Serpent::addBlock()
{
    if (tete->suivant == nullptr) // si le serpent n'est constitué que d'une tête
    {
        Block * new_block = new Block("sprite/snake/defaut/1.png", tete->depart.x-32, tete->depart.y);
        tete->suivant = queue = new_block;
        queue->precedent = tete;
    }

    else // si le serpent est constitué d'une tête et d'une queue ou d'un corps
    {
        Block * new_block;

        if (tete->direction == "none")
        {
            new_block = new Block("sprite/snake/defaut/2.png", queue->depart.x-32, queue->depart.y);
        }
        else
        {
            queue->setSprite(Texture("sprite/snake/defaut/1.png"));
            new_block = new Block("sprite/snake/defaut/2.png", queue->depart.x, queue->depart.y);
        }
        queue->setSprite(Texture("sprite/snake/defaut/1.png"));

        queue->suivant = new_block;
        new_block->precedent = queue;
        queue = new_block;
    }
}

bool Serpent::OutOfBounds(float offsetX, float offsetY)
{   
    if (tete->position.x -16 < offsetX || tete->position.x -16 > offsetX+512-32 || tete->position.y -16 < offsetY || tete->position.y -16 > offsetY+512-32) return true; 
    return false;
}

bool Serpent::Hit()
{
    Block * block = tete->suivant;
    while (block != nullptr)
    {
        if (tete->arrivee.x == block->arrivee.x && tete->arrivee.y == block->arrivee.y) return true;
        block = block->suivant;
    }
    return false;
}

void Serpent::setDirection(std::string direction)
{
    if (tete->onCase()) tete->direction = direction;
}

void Serpent::setArrivee()
{
    if (tete->onCase())
    {   
        if (tete->direction == "up") tete->arrivee.y = tete->depart.y -32;
        if (tete->direction == "down") tete->arrivee.y = tete->depart.y +32;
        if (tete->direction == "left") tete->arrivee.x = tete->depart.x -32;
        if (tete->direction == "right") tete->arrivee.x = tete->depart.x +32;
    }
}

std::string Serpent::getDirection()
{
    return tete->direction;
}

Block* Serpent::getTete()
{
    return tete;
}