#include "../include/snake.h"


Block::Block(Texture texture, float x, float y) :
    sprite(new Sprite(texture)),
    velocity(4),
    direction("none"),
    initPos(x, y),
    currentPos(x, y),
    destPos(x, y),
    next(nullptr),
    previous(nullptr)
{
    sprite->setPosition(currentPos.x, currentPos.y);
    sprite->setOrigin(16, 16);
}

Block::~Block()
{
}

void Block::update()
{
    setInitPos();
    setDestPos();
    setDirection();

    move();

    sprite->setPosition(currentPos.x, currentPos.y);
}

bool Block::onCell()
{
    if (int(currentPos.x - 16) %32 == 0 && int(currentPos.y + 8) %32 == 0) // une case fait 32/32
    {
        return true;
    }
    return false;
}

void Block::moveUp()
{
    currentPos.y -= velocity;
}

void Block::moveDown()
{
    currentPos.y += velocity;
}

void Block::moveLeft()
{
    currentPos.x -= velocity;
}

void Block::moveRight()
{
    currentPos.x += velocity;
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
    if (onCell() && previous != nullptr)
    {
        if (currentPos.x > previous->initPos.x) this->direction = "left";
        else if (currentPos.x < previous->initPos.x) this->direction = "right";
        else if (currentPos.y > previous->initPos.y) this->direction = "up";
        else if (currentPos.y < previous->initPos.y) this->direction = "down";
    }
}

void Block::setInitPos()
{
    if (onCell()) initPos = currentPos;
}

void Block::setDestPos()
{
    if (onCell() && previous != nullptr) destPos = previous->initPos;
}

void Block::setSprite(Texture texture)
{
    sprite->setTexture(texture);
}

Vector2f Block::getCurrentPos()
{
    return currentPos;
}

Vector2f Block::getDestPos()
{
    return destPos;
}

Sprite * Block::getSprite()
{
    return sprite;
}

Block * Block::getNext()
{
    return next;
}





Snake::Snake(float x, float y) : 
    head(new Block(Texture("sprite/snake/0.png"), x, y)),
    tail(nullptr)
    
{
    addBlock();
    addBlock();
}

Snake::~Snake()
{
    while (head != nullptr)
    {
        Block* temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
}

void Snake::update(std::string direction)
{
    setDirection(direction);
    head->setInitPos();
    setDestPos(); 
    head->move();
    head->sprite->setPosition(head->currentPos.x, head->currentPos.y);

    Block * block = head->next;
    while(block != nullptr)
    {
        block->update();
        block = block->next;
    }  
}

void Snake::addBlock()
{
    if (head->next == nullptr) // si le Snake n'est constitué que d'une tête
    {
        Block * new_block = new Block("sprite/snake/1.png", head->initPos.x-32, head->initPos.y);
        head->next = tail = new_block;
        tail->previous = head;
    }

    else // si le Snake est constitué d'une tête et d'une tail ou d'un corps
    {
        Block * new_block;

        if (head->direction == "none")
        {
            new_block = new Block("sprite/snake/2.png", tail->initPos.x-32, tail->initPos.y);
        }
        else
        {
            tail->setSprite(Texture("sprite/snake/1.png"));
            new_block = new Block("sprite/snake/2.png", tail->initPos.x, tail->initPos.y);
        }
        tail->setSprite(Texture("sprite/snake/1.png"));

        tail->next = new_block;
        new_block->previous = tail;
        tail = new_block;
    }
}

bool Snake::OutOfBounds(float offsetX, float offsetY)
{   
    if (head->currentPos.x -16 < offsetX || head->currentPos.x -16 > offsetX+512-32 || head->currentPos.y -16 < offsetY || head->currentPos.y -16 > offsetY+512-32) return true; 
    return false;
}

bool Snake::Hit()
{
    Block * block = head->next;
    while (block != nullptr)
    {
        if (head->destPos.x == block->destPos.x && head->destPos.y == block->destPos.y) return true;
        block = block->next;
    }
    return false;
}

void Snake::setDirection(std::string direction)
{
    if (head->onCell()) head->direction = direction;
}

void Snake::setDestPos()
{
    if (head->onCell())
    {   
        if (head->direction == "up") head->destPos.y = head->initPos.y -32;
        if (head->direction == "down") head->destPos.y = head->initPos.y +32;
        if (head->direction == "left") head->destPos.x = head->initPos.x -32;
        if (head->direction == "right") head->destPos.x = head->initPos.x +32;
    }
}

std::string Snake::getDirection()
{
    return head->direction;
}

Block* Snake::getHead()
{
    return head;
}