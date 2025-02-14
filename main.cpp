#include "include/game.h"

#include "Bbop-Library/include/BBOP/Graphics.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


enum main_state 
{
    in_game=0,
    in_menu=1,
    in_settings=2,
    leaving=3
};

main_state STATE = in_menu;

// laps de temps après avoir appuyé sur un bouton
void halfTime(bool &released, double &released_t, Button *&button, enum main_state etat)
{
    if (!released)
    {
        released_t = glfwGetTime();
        released = true; 
        std::string path = "sprite/iu/button/" + button->name + "/2.png";
        button->sprite->setTexture(path.c_str());
    }
    else if (glfwGetTime() - released_t > 0.3) 
    {
        std::string path;
        path = "sprite/iu/button/" + button->name + "/1.png";
        button->sprite->setTexture(path.c_str());

        released = false;
        STATE = etat;
    }
}

void startMenu(Menu *menu, Game* game, Scene scene, bool &released, double &released_t, Button *&button)
{
    scene.Use();
    game->Draw();

    if (released == false) button = menu->update();

    if(button != nullptr)
    {
        if (button->name == "start")
        {
            halfTime(released, released_t, button, in_game);
        }
        else if(button->name == "settings")
        {
            halfTime(released, released_t, button, in_settings);
        }
        else if(button->name == "exit")
        {
            halfTime(released, released_t, button, leaving);
        }
    }

    menu->Draw(scene);
}

void startGame(Game * game, Scene scene)
{
    scene.Use();
    game->update();

    if (game->isDead()) 
    {
        game->reset();
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

    Scene scene;

    Button * button = new Button;
    bool released = false;
    double released_t = glfwGetTime();

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

            case in_menu :
            {
                startMenu(menu, game, scene, released, released_t, button);
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

    delete game;
    game = nullptr;

    delete menu;
    menu = nullptr;

    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}