#include "../../include/gameplay/gameplay.h"


Gameplay::Gameplay(ScoreData& sharedScoreData) :
    scene(),
    state(GameplayState::play),
    inputManager(),
    scoreData(sharedScoreData),
    scoreManager(&scoreData, 50, "assets/fonts/Ghrathe.ttf", Vector2f(50, 200)),
    background(Sprite("assets/sprites/background/0.png")),
    ground(Sprite("assets/sprites/ground/0.png")),
    fruit(Sprite("assets/sprites/fruit/0.png")),
    score(0),
    offsetX((BBOP_WINDOW_RESOLUTION.x - ground.getSize().x) / 2),
    offsetY((BBOP_WINDOW_RESOLUTION.y - ground.getSize().y) / 2),
    snake(Snake(Vector2f((offsetX + ground.getSize().x/2 - 80), offsetY + (ground.getSize().y/2)+16)))
{
    ground.setPosition(offsetX, offsetY);

    // ground.getSize().x-y/2 milieu du plateau
    // +96 = 32*3 -> trois cases vers la droite
    fruit.setPosition(offsetX + ground.getSize().x/2 + 112, offsetY + ground.getSize().y/2 +16);
    Vector2f fruitSize = fruit.getSize();
    fruit.setOrigin(fruitSize.x/2, fruitSize.y/2);

    std::cout << "Gameplay Initialisée" << std::endl;
}

Gameplay::~Gameplay()
{
    std::cout << "Gameplay supprimée" << std::endl;
}

void Gameplay::reset()
{

    state = GameplayState::play;
    score = 0;

    // réinitialiser l'inputManager

    snake.reset();
    fruit.setPosition(offsetX + ground.getSize().x/2 + 96+16, offsetY + ground.getSize().y/2+16);
}


void Gameplay::Draw()
{
    scene.Use();
    
    scene.Draw(background);
    scene.Draw(ground);

    scene.Draw(snake);
    scene.Draw(scoreManager);

    scene.Draw(fruit);
    scene.render();
}

void Gameplay::update(GLFWwindow * window)
{
    inputManager.update(window);

    if (state == GameplayState::play) {
        updateSnake();
    }
    if (state == GameplayState::GameOver) {
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            reset();
        }
    }
}

void Gameplay::updateScore()
{
    scoreData.setGameplayScore(score);
    scoreData.updateBestScore();
    scoreData.updateTotalScore();
    scoreManager.refreshFromData();
}

void Gameplay::updateSnake()
{
    snake.update(inputManager.getInput());

    if (snake.collideFruit(fruit.getPosition())) {
        snake.addBlock();
        score++;
        updateScore();
        updateFruit();
    }
        
    if (snake.isDead(offsetX, offsetY)) {
        handleGameplayOver();
    }
}

void Gameplay::updateFruit()
{
    // chaque case fait 32 pixels
    // + offset pour être dans le cadre de jeu

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib2(0, 1);
    std::uniform_int_distribution<> distrib16(0, 15);
    int x = distrib16(gen) * 32 + offsetX + fruit.getOrigin().x;
    int y = distrib16(gen) * 32 + offsetY + fruit.getOrigin().y;


    while (snake.collideFruit(Vector2f(x, y)))
    {
        int random = distrib2(gen);

        if (random == 0) {
            x = distrib16(gen) * 32 + offsetX;
        } 
        else {
            y = distrib16(gen) * 32 + offsetY;
        }
    }

    fruit.setPosition(x, y);
}

GameplayState Gameplay::getState()
{
    return state;
}

void Gameplay::handleGameplayOver()
{
    state = GameplayState::GameOver;
    std::cout << "Vous êtes mort" << std::endl;
}