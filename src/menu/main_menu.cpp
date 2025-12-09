#include "../../include/menu/main_menu.h"
#include <fstream>


MainMenu::MainMenu(ScoreData& sharedScoreData, TimeData& sharedTimeData) :
    m_scene(),
    m_board(Sprite("assets/sprites/iu/board.png")),
    m_state(MenuState::In),
    m_scoreData(sharedScoreData),
    m_timeData(sharedTimeData),
    m_scoreManager(&m_scoreData, 25, "assets/fonts/Ghrathe.ttf", Vector2f(600, 300), Vector2f(600, 350), Vector2f(600, 400)),
    m_timeManager(&m_timeData, 25, "assets/fonts/Ghrathe.ttf", Vector2f(900, 300), Vector2f(900, 350), Vector2f(900, 400)),
    m_inputManager(),
    m_buttonManager(),
    m_speedTransition(30)
{
    std::cout << "MainMenu initialisé" << std::endl;
}

MainMenu::~MainMenu()
{
    std::cout << "MainMenu supprimé" << std::endl;
}

void MainMenu::Draw()
{
    m_scene.Use();
    m_scene.Draw(m_board);
    m_scene.Draw(m_scoreManager);
    m_scene.Draw(m_timeManager);
    m_scene.Draw(m_buttonManager);
    m_scene.render();
}

void MainMenu::updateScore()
{
    m_scoreManager.refreshFromData();
}

void MainMenu::update(GLFWwindow * window, float deltaTime)
{
    if (m_inputManager.getInput() != InputMenu::Select) {
        m_inputManager.update(window);
        m_buttonManager.update(m_inputManager.getInput(), deltaTime);
    }
}

void MainMenu::transitionOut(float deltaTime)
{
    Vector2f boardPos = m_board.getPosition();

    if (boardPos.y > - m_board.getSize().y) 
    {
        Vector2f velocity = Vector2f(0, m_speedTransition*-1);

        // déplace tous les éléments de la scène
        m_board.setPosition(boardPos.x + velocity.x*deltaTime, boardPos.y + velocity.y*deltaTime);
        m_buttonManager.moveTo(velocity, deltaTime);
        m_scoreManager.moveTo(velocity, deltaTime);
        m_timeManager.moveTo(velocity, deltaTime);
        m_speedTransition+=20;
    }
    else {
        m_state = MenuState::Out;
        m_inputManager.reset();
        m_speedTransition=30;
    }
}

void MainMenu::transitionIn(float deltaTime)
{
    Vector2f boardPos = m_board.getPosition();

    if (boardPos.y < 0) 
    {
        // déplace tous les éléments de la scène
        
        Vector2f velocity = Vector2f(0, m_speedTransition);        
        m_board.setPosition(boardPos.x + velocity.x*deltaTime, boardPos.y + velocity.y*deltaTime);
        m_buttonManager.moveTo(velocity, deltaTime);
        m_scoreManager.moveTo(velocity, deltaTime);
        m_timeManager.moveTo(velocity, deltaTime);
        m_speedTransition+=20;
    }
    else {
        m_state = MenuState::In;
        updateScore();
        m_timeManager.refreshFromData();
        std::cout << "refresh" << std::endl;
    }
}

bool MainMenu::transitionComplete()
{
    return m_state == MenuState::Out;
}

bool MainMenu::selectDelayOver()
{
    return m_buttonManager.selectTimestampOver();
}

bool MainMenu::buttonSelected(ButtonName buttonName)
{
    return m_buttonManager.buttonSelected(buttonName, m_inputManager.getInput());
}

MenuState MainMenu::getState()
{
    return m_state;
}