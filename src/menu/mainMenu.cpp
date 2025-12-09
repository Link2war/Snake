#include "../../include/menu/mainMenu.h"
#include <fstream>


MainMenu::MainMenu(ScoreData& sharedScoreData, TimeData& sharedTimeData) :
    scene(),
    board(Sprite("assets/sprites/iu/board.png")),
    state(MenuState::In),
    scoreData(sharedScoreData),
    timeData(sharedTimeData),
    scoreManager(&scoreData, 25, "assets/fonts/Ghrathe.ttf", Vector2f(600, 300), Vector2f(600, 350), Vector2f(600, 400)),
    timeManager(&timeData, 25, "assets/fonts/Ghrathe.ttf", Vector2f(900, 300), Vector2f(900, 350), Vector2f(900, 400)),
    buttonManager(),
    
    speedTransition(30)
{
    std::cout << "MainMenu initialisé" << std::endl;
}

MainMenu::~MainMenu()
{
    std::cout << "MainMenu supprimé" << std::endl;
}

void MainMenu::Draw()
{
    scene.Use();
    scene.Draw(board);
    scene.Draw(scoreManager);
    scene.Draw(timeManager);
    scene.Draw(buttonManager);
    scene.render();
}

void MainMenu::updateScore()
{
    std::cout << scoreData.getTotalScore() <<std::endl;
    scoreManager.refreshFromData();
}

void MainMenu::update(GLFWwindow * window, float deltaTime)
{
    if (inputManager.getInput() != InputMenu::Select) {
        inputManager.update(window);
        buttonManager.update(inputManager.getInput(), deltaTime);
    }
}

void MainMenu::transitionOut(float deltaTime)
{
    Vector2f boardPos = board.getPosition();

    if (boardPos.y > - board.getSize().y) 
    {
        Vector2f velocity = Vector2f(0, speedTransition*-1);

        // déplace tous les éléments de la scène
        board.setPosition(boardPos.x + velocity.x*deltaTime, boardPos.y + velocity.y*deltaTime);
        buttonManager.moveTo(velocity, deltaTime);
        scoreManager.moveTo(velocity, deltaTime);
        timeManager.moveTo(velocity, deltaTime);
        speedTransition+=20;
    }
    else {
        state = MenuState::Out;
        inputManager.reset();
        speedTransition=30;
    }
}

void MainMenu::transitionIn(float deltaTime)
{
    Vector2f boardPos = board.getPosition();

    if (boardPos.y < 0) 
    {
        // déplace tous les éléments de la scène
        
        Vector2f velocity = Vector2f(0, speedTransition);        
        board.setPosition(boardPos.x + velocity.x*deltaTime, boardPos.y + velocity.y*deltaTime);
        buttonManager.moveTo(velocity, deltaTime);
        scoreManager.moveTo(velocity, deltaTime);
        timeManager.moveTo(velocity, deltaTime);
        speedTransition+=20;
    }
    else {
        state = MenuState::In;
        updateScore();
    }
}

bool MainMenu::transitionComplete()
{
    return state == MenuState::Out;
}

bool MainMenu::selectDelayOver()
{
    return buttonManager.selectTimestampOver();
}

bool MainMenu::buttonSelected(ButtonName buttonName)
{
    return buttonManager.buttonSelected(buttonName, inputManager.getInput());
}

MenuState MainMenu::getState()
{
    return state;
}