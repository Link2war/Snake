#pragma once


class TimeData
{
private :
    float time; // temps de la partie
    float bestTime; // meilleur temps

public :
    /**
     * @brief Constructeur de la classe TimeData
     * @note Initialise les données à 0
     */
    TimeData();

    /**
     * @brief Réinitialise les données à 0
     */
    void reset();

    /**
     * @brief Modifie le temps de la partie
     * @param _time Nouveau temps de la partie
     */
    void setGameplayTime(float _time);

    /**
     * @brief Met à jour le meilleur temps
     */
    void updateBestTime();

    /**
     * @brief Retourne le temps de la partie
     */
    float getGameplayTime() const;

    /**
     * @brief Retourne Le meilleur temps
     */
    float getBestTime() const;
};