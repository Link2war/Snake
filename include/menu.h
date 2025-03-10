#pragma once

#include <BBOP/Graphics.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string>

#include "iu.h"

enum menu_input
{
    menu_up = 0,
    menu_down = 1,
    menu_select = 2,
    menu_null = 3,
};

class Menu
{
    private :
        GLFWwindow * window; // Fenêtre glfw
        Scene scene; // Scène du menu

        Sprite * board; // panneau du menu
        Button * currentButton; // pointeur sur le bouton survolé ou sélectionné

        // naviguation du menu
        bool released; // si la touche à été relaché avant de prendre un autre input
        double released_t; // timing depuis le dernière appuis

        // sortie/entrer du menu
        bool quit; // si le joueur a séléctionné un Button
        bool enter; // si le joueur retourne dans le menu
        int speedTransition;
        

    public :
        /* @brief Constructeur de la classe Menu
        @note Initialise les boutons du menu en récupérant les données du fichier info_button.txt
        @note Créer une liste chaînée circulaire en reliant le premier pointeur vers le dernier
        */
        Menu(GLFWwindow * window);

        /* @brief Destructeur de la classe Menu
        @note Désallocation de chaque pointeur
        @note - Prend un bouton de départ pour arréter la boucle
        */
        ~Menu();

        /* @brief Affichage des différents Sprite dans la scène de jeu
        @param scene Attribut Scene de la classe Game
        */
        void Draw();

        /* @brief Gère la naviguation dans le menu
        @return menu_input : input sélectionné selon l'action lié
        @note Renvoie l'input (un entier) correspondant à l'action choisie
        */
        menu_input navigation();

        /* @brief Mise à jour du Menu
        @return current_button : bouton sur lequel le joueur se trouve
        @note Met à jour les sprites des boutons ainsi que le current_button
        */
        Button * update();

        /* @brief initialise tous les boutons du menu
        @note utilise initButton pour générer chaque button
        */
        void initMenuButtons();

        /* @brief Modifie le bouton
        @note Change la texture du sprite et l'état du bouton selon son état actuel
        */
        void setButton(Button *& button);

        /* @brief retourne le nom du Button sélectionné
        */
        std::string getButtonName();

        /* @brief Laps de temps après avoir appuyé sur un bouton
        @return end_half_time : retourne true si le halftime est terminé
        */
        bool halfTime();

        /* @brief si le joueur doit quitter le menu et que la transition n'est pas terminée
        @note si un bouton est sélectionné ou si le bool quit est true
        */
        bool quitMenu();

        /* @brief si le joueur doit retourner dans le menu et que la transition n'est pas terminée
        @note lancé quand la partie est terminé
        */
        bool enterMenu();

        /* @brief transition du menu vers la game ou les settings
        @return état de la transition
        @note déplace tous les éléments de la scène vers le haut
        */
        bool transitionOut();

        /* @brief transition de la game ou des settings vers le menu
        @return état de la transition
        @note déplace tous les éléments de la scène vers le bas
        */
        bool transitionIn();
};