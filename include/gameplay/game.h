#pragma once

#include <BBOP/Graphics.h>
#include "../utils/timer.h"
#include "gameplay_state.h"
#include "../core/input/input_manager.h"
#include "managers/game_score_manager.h"
#include "managers/game_time_manager.h"
#include "game_board.h"
#include "../entities/snake/snake.h"
#include "items/game_item.h"

#include <random>




class Game
{
private :
    Scene m_scene; // Scène de jeu
    GameplayState m_state; // état de Gameplay
    
    ScoreData m_scoreData; // Donées des scores (variable de GameplayLoop)
    TimeData m_timeData;

    GameScoreManager m_scoreManager; // gère le score de la partie
    GameTimeManager m_timeManager;
    InputManager m_inputManager; // input de Gameplay

    Texture m_boardTexture;
    Texture m_itemTexture;

    GameBoard m_board;
    Snake m_snake; // Pointeur du serpent utilisé par le joueur
    GameItem m_fruit;

    Sprite m_background; // Sprite du sol (premier plan)
    

    Timer m_timer;
    float m_time;
    int m_score; // score de la partie


public :
    /**
     * @brief Constructeur de la classe Gameplay
     * @note Initialisation :
     * @note - Tous les attributs de la classe Gameplay
     * @note - Change la position de l'arrière plan
     * @note - Ajoute un fruit à la partie
     */
    Game(ScoreData& sharedScoreData, TimeData& sharedTimeData); 

    /**
     * @brief Destructeur de la classe Gameplay
     * @note Désalloue le snake
     */
    ~Game(); 

    /**
     * @brief Réinitialise la partie
     * @note - Remet l'etat de la partie en Gameplay
     * @note - Met la direction par defaut (none)
     * @note - Créer un nouveau snake de taille standard, La position du snake est gérer lors de son initialisation
     * @note - Remet la position par defaut du fruit
     */
    void reset();

    /**
     * @brief Affiche les éléments de la partie sur la scène de la classe Gameplay
     * @note Affiche :
     * @note - l'arrière plan
     * @note - le plateau de jeu
     * @note - les blocks composant le snake
     * @note - le fruit à récupérer
     */
    void Draw(); 

    /**
     * @brief Met à jour la partie
     * @note - met à jour l'input de direction
     * @note - met à jour l'etat de partie Gameplay
     */
    void update(GLFWwindow * window, float deltaTime); 

    /**
     * @brief Met à jour le scoreManager
     */
    void updateScore();

    /**
     * @brief Met à jour le timeManager
     */
    void updateTime();

    /**
     * @brief Met à jour le Snake
     */
    void updateSnake(float deltaTime);

    /**
     * @brief Modifie la position du fruit sur le plateau
     * @note Déplace le fruit sur une case vide choisie aléatoirement
     */
    void moveItem();

    /**
     * @brief Retourne l'Etat de la partie
     */
    GameplayState getState();

    /**
     * @brief Change l'etat de la partie en GameplayOver
     */
    void handleGameplayOver();
};