#include "../include/game.h"


Game::Game(GLFWwindow * window_) :
    window(window_),
    camera(Vector2f(BBOP_WINDOW_SIZE.x/2, BBOP_WINDOW_SIZE.y/2), 0.7),
    background(new Sprite("sprite/sol/512.png")),
    fruit(new Sprite("sprite/fruit/0.png")),
    offsetX(704),
    offsetY(288),
    is_playing(false),
    is_dead(false),
    direction("none")
{
    background->setPosition(offsetX, offsetY);

    blocks.push_back(Block(offsetX+256, offsetY+256));
    blocks.push_back(Block(offsetX+256-32, offsetY+256));

    setFruit();
}

Game::~Game()
{
    is_playing = false;
    is_dead = false;
}

bool Game::isAlive()
{
    return !is_dead;
}

void Game::update()
{
    scene.useCamera(&camera);
    
    // direction donné par le joueur
    getDirection();

    if (is_playing) 
    {
        // si le joueur est sur la meme case qu'un fruit, on deplace le fruit et on ajoute un bloc au serpent
        checkFruit();

        // mise a jour des positions de depart et d'arivée de chaque bloc
        checkPosition();

        // mise a jour de la direction de chaque bloc
        checkDirection();

        // affichage de tous les blocs
        for (long unsigned int i=0; i<blocks.size(); i++)
        {
            blocks[i].update();
        }
        
        // verifie si le bloc tete est a l'exterieur des limites
        checkOutOfBounds();
        checkHit();
        if(is_dead) 
        {
            is_playing = false;
        }
    }
    
    Draw();
}

void Game::Draw()
{
    scene.Use();
    scene.Draw(*background);

    for (long unsigned int i=0; i<blocks.size(); i++)
    {
        scene.Draw(*blocks[i].getSprite());
    }

    scene.Draw(*fruit);
}

void Game::checkOutOfBounds()
{
    Vector2f position = blocks[0].getPositionActuelle();

    if (position.x < offsetX || position.x > offsetX+512-32 || position.y < offsetY || position.y > offsetY+512-32) is_dead = true; 
}

void Game::checkHit()
{
    Vector2f pos = blocks[0].getPositionActuelle();

    for (long unsigned int i=1; i<blocks.size(); i++)
    {
        Vector2f pos_i = blocks[i].getPositionActuelle();

        if (pos.x == pos_i.x && pos.y == pos_i.y) is_dead = true;
    }
}

void Game::checkDirection()
{
    for (long unsigned int i=0; i<blocks.size(); i++)
    {
        if (i == 0) blocks[i].setDirection(nullptr);
        else blocks[i].setDirection(&blocks[i-1]);
    }
    
}

void Game::checkPosition()
{
    for (long unsigned int i=0; i<blocks.size(); i++)
    {
        if (blocks[i].onCase())
        {
            // reinitialise toutes les positions de depart 
            blocks[i].setPositionDepart(blocks[i].getPositionActuelle());

            // change la position d'arrivée de la tete puis du reste du corps
            if (i==0) blocks[i].setPositionTete(direction);
            else blocks[i].setPositionArrivee(blocks[i-1].getPositionDepart());
        }
    }
}


void Game::getDirection()
{
    if (direction == "none")
    {
        if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
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
        if ((glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && blocks[0].getDirection() != "down")
        {
            direction = "up";
        }
        if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && blocks[0].getDirection() != "up")
        {
            direction = "down";
        }
        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) && blocks[0].getDirection() != "right")
        {
            direction = "left";
        }
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) && blocks[0].getDirection() != "left")
        {
            direction = "right";
        }
    }

    // appuyer sur n'importe quelle direction pour que la partie commence
    if(is_playing == false && direction != "none")
    {
        is_playing = true;
    }
}

void Game::addBlock()
{
    // par rapport a la position de depart juste avant qu'il soit mis a jour
    Vector2f position = blocks.back().getPositionDepart();
    blocks.push_back(Block(position.x, position.y));
}

void Game::setFruit()
{
    // 704 / 704+512-32 et 288 / 288+512-32
    // 16*16/32p

    // genere une position aleatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 16);
    int abs = distrib(gen) * 32 + offsetX -32;
    int ord = distrib(gen) * 32 + offsetY -32;

    // on verifie si cette position n'est pas deja prise par un block du serpent
    for (long unsigned int i=0; i<blocks.size(); i++)
    {
        if (abs == blocks[i].getPositionActuelle().x || ord== blocks[i].getPositionActuelle().y)
        {
            if (abs == blocks[i].getPositionActuelle().x) abs = distrib(gen) * 32 + offsetX -32;
            else ord = distrib(gen) * 32 + offsetY -32;
            i = 0;
        }
    }

    // ajoute le fruit
    fruit->setPosition(abs, ord);
}

void Game::checkFruit()
{
    for (long unsigned int i=0; i<blocks.size(); i++)
    {
        Vector2f pos_block = blocks[i].getPositionActuelle();
        Vector2f pos_fruit = fruit->getPosition();

        if (pos_block.x == pos_fruit.x && pos_block.y == pos_fruit.y)
        {
            addBlock();
            setFruit();
        }
    }
}