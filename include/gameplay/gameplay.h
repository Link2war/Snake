#pragma once

#include <BBOP/Graphics.h>
#include "../gameCharacters/snake.h"
#include "inputManagerGameplay.h"
#include "../ui/scoreManagerGameplay.h"

#include <random>

/**
 * @brief Etat de la partie
 * @note Gameplay : partie en cours
 * @note GameplayOver : partie terminée
 */
enum class GameplayState
{
    play,
    GameOver
};


class Gameplay
{
private :
    Scene scene; // Scène de jeu
    GameplayState state; // état de Gameplay
    InputManagerGameplay inputManager; // input de Gameplay
    ScoreData scoreData; // Donées des scores (variable de GameplayLoop)
    ScoreManagerGameplay scoreManager; // gère le score de la partie

    Sprite background; // Sprite de l'arrière plan
    Sprite ground; // Sprite du sol (premier plan)
    Sprite fruit; // Sprite du fruit

    int score; // score de la partie

    float offsetX; // Offset de largeur
    float offsetY; // Offset de hauteur

    Snake snake; // Pointeur du serpent utilisé par le joueur


public :
    /**
     * @brief Constructeur de la classe Gameplay
     * @note Initialisation :
     * @note - Tous les attributs de la classe Gameplay
     * @note - Change la position de l'arrière plan
     * @note - Ajoute un fruit à la partie
     */
    Gameplay(ScoreData& sharedScoreData); 

    /**
     * @brief Destructeur de la classe Gameplay
     * @note Désalloue le snake
     */
    ~Gameplay(); 

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
    void update(GLFWwindow * window); 

    /**
     * @brief Met à jour le scoreManager
     */
    void updateScore();

    /**
     * @brief Met à jour le Snake
     */
    void updateSnake();

    /**
     * @brief Modifie la position du fruit sur le plateau
     * @note Déplace le fruit sur une case vide choisie aléatoirement
     */
    void updateFruit();

    /**
     * @brief Retourne l'Etat de la partie
     */
    GameplayState getState();

    /**
     * @brief Change l'etat de la partie en GameplayOver
     */
    void handleGameplayOver();
};