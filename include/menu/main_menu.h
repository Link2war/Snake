#pragma once

#include <BBOP/Graphics.h>
#include "menu_state.h"
#include "../ui/button_manager.h"
#include "managers/menu_score_manager.h"
#include "managers/menu_time_manager.h"
#include "input/menu_input_manager.h"


class MainMenu
{
private :
    Scene m_scene; // Scène du Mainmenu
    Sprite m_board; // panneau du MainMenu
    MenuState m_state; // état du MainMenu
    ScoreData m_scoreData; // données du score (variable de GameLoop)
    TimeData m_timeData;
    MenuScoreManager m_scoreManager; // gère le score du Mainmenu
    MenuTimeManager m_timeManager;
    MenuInputManager m_inputManager; // gère les inputs du Mainmenu
    ButtonManager m_buttonManager; // gère les boutons du Mainmenu

    // Sprite background // nuages à déplacer

    int m_speedTransition; // vitesse de transition entre le Mainmenu et un autre état de la partie

public :
    /**
     * @brief Constructeur de la classe MainMenu
     * @note Initialise les boutons du MainMenu
     * @note Créer une liste chaînée circulaire en reliant le premier pointeur vers le dernier
     */
    MainMenu(ScoreData& sharedScoreData, TimeData& sharedTimeData);

    /**
     * @brief Destructeur de la classe MainMenu
     */
    ~MainMenu();

    /**
     * @brief Affichage des différents Sprite dans la scène du MainMenu
     * @note Le MainMenu est affiché par dessus la Game
     */
    void Draw();

    /**
     * @brief Mise à jour du MainMenu
     * @note - Met à jour l'input
     * @note - Met à jour le délai de changement de bouton
     * @note - Met à jour le bouton survolé
     */
    void update(GLFWwindow * window, float deltaTime);

    /**
     * @brief Met à jour le score du Mainmenu
     */
    void updateScore();

    /**
     * @brief Gère la transition du MainMenu vers un autre état de la Game
     * @note déplace tous les éléments de la scène vers le haut
     */
    void transitionOut(float deltaTime);

    /**
     * @brief Gère la transition d'un etat de la Game vers le Mainmenu
     * @note déplace tous les éléments de la scène vers le bas
     */
    void transitionIn(float deltaTime);

    /**
     * @brief Retourne l'état de la transition Out si elle est terminé ou non
     */
    bool transitionComplete();

    /**
     * Retourne true si le délai de selction de bouton est terminé
     */
    bool selectDelayOver();

    /**
     * @brief Retourne true si le Button est selctionné
     * @param buttonName Nom du Button
     */
    bool buttonSelected(ButtonName buttonName);

    /**
     * @brief Retourne l'état du MainMenu
     */
    MenuState getState();
};