#pragma once

#include <BBOP/Graphics.h>
#include "../utils/timer.h"
#include "../data/score_data.h"
#include "../data/time_data.h"
#include "../gameplay/game.h"
#include "../menu/main_menu.h"
#include "../settings/settings_menu.h"

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
    GLFWwindow * m_window; // fenetre GLFW
    ScoreData m_scoreData; // Donées des scores (dernier score, record, score accumulé)
    TimeData m_timeData;
    Game m_gameplay; // partie du jeu
    MainMenu m_mainMenu; // menu du jeu
    SettingsMenu m_settingsScreen; // settings
    LoopState m_state; // état de la boucle de jeu
    Timer m_timer;
    double m_deltaTime;

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
    GameLoop(GLFWwindow * window);

    /**
     * @brief Destructeur de la classe
     */
    ~GameLoop();

    /**
     * @brief Boucle principale du jeu
     * @note Gère les différents états du jeu
     */
    void run();

    void updateDeltaTime();

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