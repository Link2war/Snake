#include "../include/gameLoop.h"

GameLoop::GameLoop(GLFWwindow * _window) :
    window(_window),
    scoreData(),
    gameplay(scoreData),
    mainMenu(scoreData),
    settingsScreen(),
    state(LoopState::MainMenu),
    deltaTime(0.0f),
    lastTime(glfwGetTime())
{
    std::cout << "boucle de jeu initialisée" << std::endl;
}

GameLoop::~GameLoop()
{
    std::cout << "Boucle de jeu supprimée" << std::endl;
}

void GameLoop::run()
{
    while (!glfwWindowShouldClose(window))
    {
        // clear de la fenêtre en noire
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);

        updateDeltaTime();

        switch (state)
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
        glfwSwapBuffers(window);
        // recupération des events glfw
        glfwPollEvents();
    }
}

void GameLoop::updateDeltaTime()
{
    float time = glfwGetTime();
    deltaTime = time - lastTime;
    lastTime = time;
}

void GameLoop::updateMenu()
{
    mainMenu.update(window, deltaTime);

    if (mainMenu.getState() == MenuState::Out) {
        mainMenu.transitionIn(deltaTime);
    }

    if (mainMenu.getState() == MenuState::In) 
    {
        if (mainMenu.buttonSelected(ButtonName::Exit)) {
            state = LoopState::Exit;
        }

        if (mainMenu.buttonSelected(ButtonName::Settings)) 
        {
            if (mainMenu.selectDelayOver()) 
            {
                mainMenu.transitionOut(deltaTime);
                if (mainMenu.transitionComplete()) {
                    state = LoopState::Settings;
                }
            }
        }

        if (mainMenu.buttonSelected(ButtonName::Play)) 
        {
            if (mainMenu.selectDelayOver()) 
            {
                mainMenu.transitionOut(deltaTime);
                if (mainMenu.transitionComplete()) {
                    state = LoopState::Game;
                }
            }
        }
    }    
}

void GameLoop::updateSettings()
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        state = LoopState::MainMenu;
    }
}

void GameLoop::updateGame()
{
    gameplay.update(window, deltaTime);
    
    if (gameplay.getState() == GameplayState::GameOver && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        state = LoopState::MainMenu;
    }
}

void GameLoop::drawMenu()
{
    gameplay.Draw();
    mainMenu.Draw();
}

void GameLoop::drawGame()
{
    gameplay.Draw();
}

void GameLoop::drawSettings()
{
    settingsScreen.Draw();
}