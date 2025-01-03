#pragma once

#include <BBOP/Graphics/cameraClass.h>
#include <BBOP/Graphics/fontsClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>

#include <vector>
#include <string>
#include <random>

#include "serpent.h"

class Game
{
    private :
        GLFWwindow * window; // Fenêtre glfw
        Scene scene; // Scène de jeu
        Camera camera; // Caméra du jeu

        float offsetX; // Offset de largeur
        float offsetY; // Offset de hauteur

        Sprite * background; // Pointeur du sprite d'arrière plan
        Serpent * serpent; // Pointeur du serpent utilisé par le joueur
        Sprite * fruit; // Pointeur du sprite de l'objet à collecter

        bool is_playing; // État de la partie
        bool launch; // lancement de la partie
        std::string direction; // Input de direction

    public :
        /* @brief Constructeur de la classe Game
        @param window Fenetre glfw
        @note Initialisation :
        @note - Tous les attributs de la classe Game
        @note - Change la position de l'arrière plan
        @note - Ajoute un fruit à la partie
        */
        Game(GLFWwindow * window_); 

        // Destructeur de la classe Game
        ~Game(); 

        /* @brief Réinitialise la partie
        @note Remise à zéro des informations
        @note - État du jeu en false
        @note - Input de direction en none
        @note - Destruction du serpent, attribue un nouveau serpent
        @note - déplacement de la pomme à sa position par défaut
        */
        void reset();

        /* @brief Récupère les inputs de direction
        @note - La partie commence quand le joueur choisie une direction entre HAUT, BAS, DROITE
        @note - Récupère la direction du serpent pour éviter d'aller en sens inverse (180°)
        */
        void getDirection(); 

        /* @brief Mise à jour du jeu à chaque frame 
        @note - Caméra à utiliser
        @note - Récupère l'input de direction
        @note - Vérifiaction de collision avec le fruit
        @note - Mise à jour des blocks
        @note - Verification de mort
        @note - Affichage
        */
        void update(); 

        /* @brief Retourne true si la partie est en cours sinon false
        @note Récupéré à chaque frame pour mettre à jour l'état de la partie
        */
        bool isPlaying();

        /* @brief Retourne true si la partie est lancée, passe à false quand la partie est terminée
        @note Récupéré par le main pour démarrer une partie
        */
        bool launched();

        /* @brief Affiche tous les objets du jeu
        @note - Scène
        @note - Arrière plan
        @note - Serpent
        @note - Fruit
        */
        void Draw(); 
        
        /* @brief Ajoute un fruit
        @note Déplace le fruit existant sur une case vide choisie aléatoirement
        @note - Une case est vide s'il n'y a pas de block sur cette case
        */
        void setFruit();

        /* @brief vérifie si le joueur à mangé un fruit 
        @note - Fait grandir le joueur
        @note - Ajoute un fruit lorsque le joueur en mange un
        @note - A FAIRE Augmente le compteur de score de 1 point
        */
        void checkFruit();
};