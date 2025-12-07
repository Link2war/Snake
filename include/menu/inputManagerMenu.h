#pragma once

#include <BBOP/Graphics.h>

#ifndef INPUT_MENU
#define INPUT_MENU
enum class InputMenu
{
    Up,
    Down,
    Select,
    Null
};
#endif

class InputManagerMenu
{
private:
    InputMenu input; // input du Menu

public:
    /**
     * @brief Constructeur de la classe InputManager
     */
    InputManagerMenu();

    /**
     * @brief Destructeur de la classe InputManager
     */
    ~InputManagerMenu();

    /**
     * @brief Mise à jour de l'input de direction
     * @param GLFWwindow sert à récupérer l'input du clavier
     * @note ! l'input est réinitialisé à chaque appelle
     */
    void update(GLFWwindow * window);

    /**
     * @brief Retourne l'input de direction
     */
    InputMenu getInput();

    /**
     * @brief Réinitialise l'input
     */
    void reset();
};