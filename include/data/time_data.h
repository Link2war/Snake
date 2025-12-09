#pragma once


class TimeData
{
private :
    float m_lastTime; // temps de la partie en secondes
    float m_bestTime; // meilleur temps

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
     * @param time Nouveau temps de la partie
     */
    void setLastTime(float time);

    /**
     * @brief Met à jour le meilleur temps
     */
    void updateBestTime();

    /**
     * @brief Retourne le temps de la partie
     */
    float getLastTime() const;

    /**
     * @brief Retourne Le meilleur temps
     */
    float getBestTime() const;
};