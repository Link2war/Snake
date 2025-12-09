#include "../../include/core/game_loop.h"

GameLoop::GameLoop(GLFWwindow* window) :
    m_window(window),
    m_scoreData(),
    m_timeData(),
    m_gameplay(m_scoreData, m_timeData),
    m_mainMenu(m_scoreData, m_timeData),
    m_settingsScreen(),
    m_state(LoopState::MainMenu),
    m_timer(),
    m_deltaTime(0.0f)
{
    std::cout << "boucle de jeu initialisée" << std::endl;
}

GameLoop::~GameLoop()
{
    std::cout << "Boucle de jeu supprimée" << std::endl;
}

void GameLoop::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        // clear de la fenêtre en noire
        bbopCleanWindow(m_window,Vector3i(0,0,0),1.0f);

        updateDeltaTime();

        switch (m_state)
        {
        case LoopState::MainMenu :
            updateMenu();
            drawMenu();
            break;

        case LoopState::Settings :
            updateSettings();
            drawSettings();
            break;

        case LoopState::Game :
            updateGame();
            drawGame();
            break;
                
        case LoopState::Exit :
            return;

        default:
            std::cerr << "Etat de boucle de jeu invalide" << std::endl;
            return;
        }
        
        // vérification des erreurs
        bbopErrorCheck();
        // swap du back buffer avec le front buffer
        glfwSwapBuffers(m_window);
        // recupération des events glfw
        glfwPollEvents();
    }
}

void GameLoop::updateDeltaTime()
{
    m_deltaTime = m_timer.elapsed();
    m_timer.reset();
}

void GameLoop::updateMenu()
{
    m_mainMenu.update(m_window, m_deltaTime);

    if (m_mainMenu.getState() == MenuState::Out) {
        m_mainMenu.transitionIn(m_deltaTime);
    }

    if (m_mainMenu.getState() == MenuState::In) 
    {
        if (m_mainMenu.buttonSelected(ButtonName::Exit)) {
            m_state = LoopState::Exit;
        }

        if (m_mainMenu.buttonSelected(ButtonName::Settings)) 
        {
            if (m_mainMenu.selectDelayOver()) 
            {
                m_mainMenu.transitionOut(m_deltaTime);
                if (m_mainMenu.transitionComplete()) {
                    m_state = LoopState::Settings;
                }
            }
        }

        if (m_mainMenu.buttonSelected(ButtonName::Play)) 
        {
            if (m_mainMenu.selectDelayOver()) 
            {
                m_mainMenu.transitionOut(m_deltaTime);
                if (m_mainMenu.transitionComplete()) {
                    m_state = LoopState::Game;
                }
            }
        }
    }    
}

void GameLoop::updateSettings()
{
    if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        m_state = LoopState::MainMenu;
    }
}

void GameLoop::updateGame()
{
    m_gameplay.update(m_window, m_deltaTime);
    
    if (m_gameplay.getState() == GameplayState::GameOver && glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        m_state = LoopState::MainMenu;
        m_gameplay.reset();
    }
}

void GameLoop::drawMenu()
{
    m_gameplay.Draw();
    m_mainMenu.Draw();
}

void GameLoop::drawGame()
{
    m_gameplay.Draw();
}

void GameLoop::drawSettings()
{
    m_settingsScreen.Draw();
}