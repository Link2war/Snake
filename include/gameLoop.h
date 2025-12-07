#pragma once

#include <BBOP/Graphics.h>
#include "data/scoreData.h"
#include "gameplay/gameplay.h"
#include "menu/mainMenu.h"
#include "settings/settingsMenu.h"

/**
 * @brief Etat de la boucle de jeu
 */
enum class LoopState
{
    MainMenu,
    Settings,
    Game,
    Exit
};

class GameLoop
{
private:
    GLFWwindow * window; // fenetre GLFW
    ScoreData scoreData; // Donées des scores (dernier score, record, score accumulé)
    Gameplay gameplay; // partie du jeu
    MainMenu mainMenu; // menu du jeu
    SettingsMenu settingsScreen; // settings
    LoopState state; // état de la boucle de jeu

public:
    /**
     * @brief Constructeur de la classe GameLoop
     * @param GLFWwindow fenetre glfw
     * @note Initialise :
     * @note - Une fenêtre
     * @note - Une partie
     * @note - Un menu
     * @note - Les settings
     * @note - L'etat de la boucle
     */
    GameLoop(GLFWwindow * _window);

    /**
     * @brief Destructeur de la classe
     */
    ~GameLoop();

    /**
     * @brief Boucle principale du jeu
     * @note Gère les différents états du jeu
     */
    void run();

    /**
     * @brief Met à jour le menu
     */
    void updateMenu();

    /**
     * @brief Met à jour la partie
     */
    void updateGame();

    /**
     * @brief Met à jour les settings
     */
    void updateSettings();

    void drawMenu();

    void drawGame();

    void drawSettings();
};