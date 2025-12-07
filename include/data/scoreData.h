#pragma once


class ScoreData
{
private :
    int score; // score de la partie
    int bestScore; // Meilleur score enregistré
    int totalScore; // score accumulé enregistré

public :
    /**
     * @brief Constructeur de la classe ScoreData
     * @note Initialise les données à 0
     */
    ScoreData();

    /**
     * @brief Réinitialise les données à 0
     */
    void reset();

    /**
     * @brief Modifie le score de la partie
     * @param _score Nouveau score de la partie
     */
    void setGameplayScore(int _score);

    /**
     * @brief Met à jour le meilleur score
     */
    void updateBestScore();

    /**
     * @brief Met à jour le score accumulé
     */
    void updateTotalScore();

    /**
     * @brief Retourne le score de la partie
     */
    int getGameplayScore() const;

    /**
     * @brief Retourne le meilleur score
     */
    int getBestScore() const;

    /**
     * @brief Retourne le score accumulé
     */
    int getTotalScore() const;
};