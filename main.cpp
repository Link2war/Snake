#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <BBOP/Graphics.h>

#include "include/game.h"

enum main_state 
{
    in_game=0,
    in_menu=1,
    in_settings=2,
    leaving=3
};
main_state STATE = in_menu;

void startMenu(Menu *menu, Game* game)
{
    game->Draw();
    menu->update();

    if (menu->quitMenu())
    {
        bool end_half_time = menu->halfTime(); // mi-temps pour l'effet d'appuis sur le Button
        if (end_half_time) // lancement de la transition ou de l'exit
        {
            if(menu->getButtonName() == "exit") STATE = leaving;

            bool end_transition = menu->transitionOut(); // transition entre deux pages
            if (end_transition) // changement de page
            {
                if (menu->getButtonName() == "play") STATE = in_game;
                else if(menu->getButtonName() == "settings") STATE = in_settings;
            }
        }
    }
    else if (menu->enterMenu())
    {
        bool end_transition = menu->transitionIn(); // transition entre deux pages
        if (end_transition) game->reset();
    }
    
    menu->Draw();
}

void startGame(Game * game, Menu * menu)
{
    game->update();
    game->Draw();

    if (game->isDead()) 
    {
        // le reset se fait après la transition
        STATE = in_menu;
    }
}

void startSettings(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) STATE = in_menu;
}


int main()
{
    //creation de la fenêtre glfw
    GLFWwindow * window;

    //initialisation de la lib
    bbopInit(1280,720,"Snake",window);
    glfwMaximizeWindow(window);
    
    std::cout << "Initialisation de la Partie" << std::endl;
    Game * game = new Game(window);
    Menu * menu = new Menu(window);

    //main while loop
    while (!glfwWindowShouldClose(window))
    {
        // clear de la fenêtre en noire
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);

        switch (STATE)
        {
            case in_game :
            {
                startGame(game, menu);
                break;
            }

            case in_menu :
            { 
                startMenu(menu, game);
                break;
            }

            case in_settings :
            {
                startSettings(window);
                break;
            }

            case leaving :
            {
                return 0;
                break;
            }

            default:
                std::cerr << "ERROR: STATE INVALID" << std::endl;
                return 1;
                break;
        }
        
        // vérification des erreurs
        bbopErrorCheck();
        // swap du back buffer avec le front buffer
        glfwSwapBuffers(window);
        // recupération des events glfw
        glfwPollEvents();
    }

    if (game) delete game;
    game = nullptr;

    if (menu) delete menu;
    menu = nullptr;

    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}