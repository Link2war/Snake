#pragma once

#include <BBOP/Graphics.h>

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string>

enum menu_input
{
    menu_up = 0,
    menu_down = 1,
    menu_select = 2,
    menu_null = 3,
};

struct Button
{
    std::string name;
    bool on;
    bool released; // si le bouton a été sélectionné
    double released_t; // timing depuis que le bouton a été selectionné

    Sprite * sprite;
    Button * next;
    Button * previous;
};

/* @brief constructeur d'un Button
@note Prend un Button en argument, lui attribut les autres valeurs mises en arguments
*/
void initButton(Button *& button, const char * name, bool on, Vector2f position, Button * next, Button * previous);


class Menu
{
    private :
        GLFWwindow * window; // Fenêtre glfw
        Scene scene; // Scène du menu

        Sprite * background; // Arrière plan du menu
        Button * current_button; // pointeur sur le bouton survolé

        // naviguation du menu
        bool released; // si la touche à été relaché avant de prendre un autre input
        double released_t; // timing depuis le dernière appuis
        bool quit; // si le joueur a séléctionné un Button

        

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
        menu_input naviguation();

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

        Button * getButton();

        /* @brief Laps de temps après avoir appuyé sur un bouton
        @return end_half_time : retourne true si le halftime est terminé
        */
        bool halfTime();

        /* @brief si le joueur doit quitter le menu
        @note si un bouton est sélectionné ou si le bool quit est true
        */
        bool quitMenu();
};