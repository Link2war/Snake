#include "../include/game.h"


Game::Game(GLFWwindow * window_) :
    window(window_),
    menu(new Menu()),
    background(new Sprite("sprite/sol/716.png")),
    serpent(new Serpent(BBOP_WINDOW_RESOLUTION.x/2 - 128 + 16, BBOP_WINDOW_RESOLUTION.y/2 - 12)),
    fruit(new Sprite("sprite/fruit/0.png")),
    offsetX((BBOP_WINDOW_RESOLUTION.x - background->getSize().x) / 2),
    offsetY((BBOP_WINDOW_RESOLUTION.y - background->getSize().y) / 2 + 4),
    is_playing(false),
    launch(true),
    direction("none")
{
    background->setPosition(offsetX, offsetY);
    fruit->setPosition(offsetX + background->getSize().x/2 + 128, offsetY + background->getSize().y/2 - 32);
}

Game::~Game()
{
    std::cout << "Vous êtes mort" << std::endl;

    delete serpent;
    serpent = nullptr;
    
    std::cout << "destruction des objets réussis" << std::endl;
}

void Game::update()
{
    scene.Use();

    if (menu->pressStart() == false) 
    {
        Draw();

        menu->onStart(window);
        menu->onSettings(window);
        menu->checkStart(window);
        menu->Draw(scene);
    }

    else
    {
        getDirection();
        if (direction != "none")
        {
            checkFruit();
            serpent->update(direction);
            if(serpent->isDead(offsetX, offsetY)) launch = false;
        }

        Draw();
    }    
}

void Game::Draw()
{
    
    scene.Draw(*background);

    Block * block = serpent->getTete();
    while (block != nullptr)
    {
        scene.Draw(*block->getSprite());
        block = block->getSuivant();
    }

    scene.Draw(*fruit);
}

void Game::reset()
{
    is_playing = false;
    launch = true;
    direction = "none";

    delete serpent;
    serpent = new Serpent(BBOP_WINDOW_RESOLUTION.x/2 - 128 + 16, BBOP_WINDOW_RESOLUTION.y/2 - 12);
    fruit->setPosition(offsetX + background->getSize().x/2 + 128, offsetY + background->getSize().y/2 - 32);

    menu->reset();
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
        if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && serpent->getDirection() != "down")
        {
            direction = "up";
        }
        if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && serpent->getDirection() != "up")
        {
            direction = "down";
        }
        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) && serpent->getDirection() != "right")
        {
            direction = "left";
        }
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) && serpent->getDirection() != "left")
        {
            direction = "right";
        }
    }

    if(is_playing == false && direction != "none") is_playing = true;
}

bool Game::launched()
{
    return launch;
}

bool Game::isPlaying()
{
    return is_playing;
}

void Game::setFruit()
{
    // chaque case fait 32 pixels
    // offset pour être dans le cadre de jeu

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 16);
    int x = distrib(gen) * 32 + offsetX+102 -32;
    int y = distrib(gen) * 32 + offsetY+102 -32;


    Block * block = serpent->getTete();
    while (block != nullptr)
    {
        if (x == block->getPosition().x && y== block->getPosition().y)
        {
            if (x == block->getPosition().x) x = distrib(gen) * 32 + offsetX+102 -32;
            else y = distrib(gen) * 32 + offsetY+102 -32;
            block = serpent->getTete();
        }

        else block = block->getSuivant();
    }

    fruit->setPosition(x, y);
}

void Game::checkFruit()
{
    Block * block = serpent->getTete();
    while (block != nullptr)
    {

        if (block->getArrivee().x -16 == fruit->getPosition().x && block->getArrivee().y - 16 == fruit->getPosition().y)
        {
            serpent->addBlock();
            setFruit();
        }

        block = block->getSuivant();
    }
}