#pragma once

#include <BBOP/Graphics.h>


class ScoreBox : public BbopDrawable
{
private :
    int m_value;
    const char* m_label; // texte
    Font* m_font; // police du texte
    TexteBox m_textBox; // boîte de texte

public :
    /**
     * @brief Constructeur de la ScoreBox
     * @param score Valeur de ScoreBox
     * @param label Texte de la boîte de texte
     * @param glyphSize Taille de la police de texte
     * @param fontPath Chemin de la police de texte
     * @param position Position de la boîte de texte
     */
    ScoreBox(int value, const char* label, int glyphSize, const char *fontPath, Vector2f position);

    /*
     * @brief Destructeur de la classe ScoreBox
     * @note Est virtual parce que la classe surchage une méthode de BbopDrawable
     * @note Désalloue la police de texte allouée dans le constructeur
     */
    virtual ~ScoreBox();

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
     * @brief Modifie la valeur de ScoreBox
     * @param score Nouvelle valeur de ScoreBox
     * @note Met à jour la boîte de texte
     */
    void setValue(float value);

    /**
     * @brief Retourne la valeur de ScoreBox
     */
    int getValue() const;

    /**
     * @brief Retourne la position de la boîte de texte
     */
    Vector2f getPosition();
};