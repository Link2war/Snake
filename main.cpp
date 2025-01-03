#include "include/game.h"

#include <BBOP/Graphics.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



int main()
{
    //creation de la fenêtre glfw
    GLFWwindow * window;

    //initialisation de la lib
    bbopInit(1920,1080,"Snake",window);


    Game game(window);

    //main while loop
    while (!glfwWindowShouldClose(window))
    {
        // clear de la fenêtre en noire
        bbopCleanWindow(window,Vector3i(0,0,0),1.0f);
        
        
        if (game.launched()) game.update();
        else game.reset();

        // FAIRE UNE FONCTION START ET UNE FONCTION PLAY


        
        
        // vérification des erreurs
        bbopErrorCheck();
        // swap du back buffer avec le front buffer
        glfwSwapBuffers(window);
        // recupération des events glfw
        glfwPollEvents();
    }
    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}