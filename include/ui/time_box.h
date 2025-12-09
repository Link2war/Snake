#pragma once

#include <BBOP/Graphics.h>


class TimeBox : public BbopDrawable
{
private :
    int m_seconds;
    int m_minutes;
    int m_hours;
    const char* m_label; // texte
    Font* m_font; // police du texte
    TexteBox m_textBox; // boîte de texte

public :
    /**
     * @brief Constructeur de la TimeBox
     * @param score Valeur de TimeBox
     * @param label Texte de la boîte de texte
     * @param glyphSize Taille de la police de texte
     * @param fontPath Chemin de la police de texte
     * @param position Position de la boîte de texte
     */
    TimeBox(const char* label, int glyphSize, const char *fontPath, Vector2f position);

    /*
     * @brief Destructeur de la classe TimeBox
     * @note Est virtual parce que la classe surchage une méthode de BbopDrawable
     * @note Désalloue la police de texte allouée dans le constructeur
     */
    virtual ~TimeBox();

    /**
     * @brief Affichage de la boîte de Texte sur l'écran
     * @note Méthode surchargée de BbopDrawable
     */
    virtual void Draw(GLint* renderUniform) const override;

    /**
     * @brief Met à jour la boîte de texte
     */
    void updateTextBox();

    /**
     * @brief Met à jour la position de la boîte de texte
     * @param position Nouvelle position de la boîte de texte
     */
    void setPosition(Vector2f position);

    /**
     * @brief Modifie la valeur de TimeBox
     * @param score Nouvelle valeur de TimeBox
     * @note Met à jour la boîte de texte
     */
    void setTime(int seconds, int minutes, int hours);

    /**
     * @brief Retourne la valeur de TimeBox
     */
    int getValue() const;

    /**
     * @brief Retourne la position de la boîte de texte
     */
    Vector2f getPosition();
};