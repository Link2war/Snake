#pragma once

#include <BBOP/Graphics.h>



class InputManager
{
private:
    Vector2i m_input; // direction x et y

public:
    /**
     * @brief Constructeur de la classe InputManager
     */
    InputManager();

    /**
     * @brief Destructeur de la classe InputManager
     */
    ~InputManager();

    /**
     * @brief Mise à jour de l'input de direction
     * @param GLFWwindow sert à récupérer l'input du clavier
     * @note ! l'input n'est pas réinitialisé
     */
    void update(GLFWwindow * window);

    /**
     * @brief Retourne l'input de direction
     */
    Vector2i getInput();
};