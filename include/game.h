#pragma once

#include <BBOP/Graphics/cameraClass.h>
#include <BBOP/Graphics/fontsClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>

#include <vector>
#include <string>
#include <random>

#include "block.h"

class Game
{
    private :
        GLFWwindow * window; // fenetre glfw
        Scene scene; // scene de jeu
        Camera camera; // camera du jeu
        Sprite * background; // arriere plan
        Sprite * fruit; // objet a collecter
        std::vector<Block> blocks; // stocke les blocks dans un vecteur

        // offset du background
        int offsetX;
        int offsetY;

        // états
        bool is_playing; // etat de la partie
        bool is_dead; // etat du joueur

        // directions 
        std::string direction; // enregistre la prochaine direction à prendre quand on arrive sur une case

    public :
        Game(GLFWwindow * window_); // constructeur de la classe Game
        ~Game(); // destructeur de la classe Game

        // appelé par le main
        void update(); // mise a jour
        bool isAlive(); // retourne true si le joueur n'est pas mort sinon false

        // appelé par update
        void Draw(); // affichage

        // Growup
        void addBlock(); // ajoute un bock
        
        // deplacement
        void checkOutOfBounds(); // verifie si le joueur est en dehors des limites
        void checkHit();
        void checkDirection(); // verifie les directions possibles
        void checkPosition(); // deplacement
        void getDirection(); // recupere les inputs de direction
        
        // fruit
        void setFruit();
        void checkFruit();
};