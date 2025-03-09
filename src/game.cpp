#include "../include/game.h"


Game::Game(GLFWwindow * _window) :
    window(_window),
    offsetX((BBOP_WINDOW_RESOLUTION.x - 512) / 2),
    offsetY((BBOP_WINDOW_RESOLUTION.y - 512) / 2),
    background(new Sprite("sprite/background/0.png")),
    ground(new Sprite("sprite/ground/0.png")),
    fruit(new Sprite("sprite/fruit/0.png")),
    snake(new Snake((offsetX + ground->getSize().x/2 - 80), offsetY + (ground->getSize().y/2)+16)),
    is_dead(false),
    start(false),
    direction("none")
{
    ground->setPosition(offsetX, offsetY);
    fruit->setPosition(offsetX + ground->getSize().x/2 + 96, offsetY + ground->getSize().y/2);

    std::cout << "Game Initialisée" << std::endl;
}

Game::~Game()
{
    std::cout << "Vous êtes mort" << std::endl;

    delete snake;
    snake = nullptr;
    
    std::cout << "Destruction des objets réussis" << std::endl;
}

void Game::update()
{
    getDirection();

    if (direction != "none")
    {
        checkFruit();
        snake->update(direction);

        if(snake->Hit() || snake->OutOfBounds(offsetX, offsetY)) 
        {
            is_dead = true;
        }
    }
}


void Game::Draw()
{
    scene.Use();
    
    scene.Draw(*background);
    scene.Draw(*ground);

    Block * block = snake->getHead();
    while (block != nullptr)
    {
        scene.Draw(*block->getSprite());
        block = block->getNext();
    }

    scene.Draw(*fruit);
    scene.render();
}

void Game::reset()
{
    is_dead = false;
    start = false;
    direction = "none";

    delete snake;
    snake = new Snake((offsetX + ground->getSize().x/2 - 80), offsetY + (ground->getSize().y/2)+16);
    fruit->setPosition(offsetX + ground->getSize().x/2 + 96, offsetY + ground->getSize().y/2);
}

void Game::getDirection()
{
    if (direction == "none")
    {
        if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
        {
            direction = "up";
        }
        if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
        {
            direction = "down";
        }
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
        {
            direction = "right";
        }
    }
    else
    {
        if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && snake->getDirection() != "down")
        {
            direction = "up";
        }
        if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && snake->getDirection() != "up")
        {
            direction = "down";
        }
        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) && snake->getDirection() != "right")
        {
            direction = "left";
        }
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) && snake->getDirection() != "left")
        {
            direction = "right";
        }
    }

    if(start == false && direction != "none") start = true;
}

bool Game::isDead()
{
    return is_dead;
}

void Game::setFruit()
{
    // chaque case fait 32 pixels
    // + offset pour être dans le cadre de jeu

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 15);
    int x = distrib(gen) * 32 + offsetX;
    int y = distrib(gen) * 32 + offsetY;


    Block * block = snake->getHead();
    while (block != nullptr)
    {
        if (x == block->getCurrentPos().x && y== block->getCurrentPos().y)
        {
            if (x == block->getCurrentPos().x) x = distrib(gen) * 32 + offsetX;
            else y = distrib(gen) * 32 + offsetY;
            block = snake->getHead();
        }

        else block = block->getNext();
    }

    fruit->setPosition(x, y);
}

void Game::checkFruit()
{
    Block * block = snake->getHead();
    while (block != nullptr)
    {

        if (block->getDestPos().x -16 == fruit->getPosition().x && block->getDestPos().y - 16 == fruit->getPosition().y)
        {
            snake->addBlock();
            setFruit();
        }

        block = block->getNext();
    }
}