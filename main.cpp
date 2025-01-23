#include "include/game.h"

#include <BBOP/Graphics.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


enum main_state 
{
    in_game=0,
    in_end_game=1,
    in_menu=2,
    in_settings=3,
    leaving=4
};

main_state STATE = in_menu;

void startMenu(Menu *menu, Game* game, Scene scene)
{
    scene.Use();
    game->Draw();

    Button * button = menu->update();

    if(button != nullptr)
    {
        if (button->name == "start")
        {
            STATE = in_game;
        }
        else if(button->name == "settings")
        {
            STATE = in_settings;
        }
        else if(button->name == "exit")
        {
            STATE = leaving;
        }
    }

    menu->Draw(scene);
}

void startGame(Game * game, Scene scene)
{
    scene.Use();
    game->update();

    if (game->isDead()) STATE = in_end_game;
}

void startEndGame(Game * game, Scene scene, GLFWwindow * window)
{
    scene.Use();
    game->Draw();

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        game->reset();
        STATE = in_menu;
    }
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

    Scene scene;

    //main while loop
    while (!glfwWindowShouldClose(window))
    {
        // clear de la fenêtre en noire
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);
        

        switch (STATE)
        {
            case in_game :
            {
                startGame(game, scene);
                break;
            }

            case in_end_game :
            {
                startEndGame(game, scene, window);
                break;
            }

            case in_menu :
            {
                startMenu(menu, game, scene);
                break;
            }

            case in_settings :
            {
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

    delete game;
    game = nullptr;

    delete menu;
    menu = nullptr;

    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}