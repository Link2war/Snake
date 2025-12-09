#pragma once

/**
 * @brief Etat de la partie
 * @note Gameplay : partie en cours
 * @note GameplayOver : partie terminée
 */
enum class GameplayState
{
    play,
    GameOver,
    Waiting
};