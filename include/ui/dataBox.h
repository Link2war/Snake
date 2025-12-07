#pragma once

#include <BBOP/Graphics.h>


class DataBox : public BbopDrawable
{
private :
    float value; // valeur (score/time)
    const char* label; // texte
    Font* font; // police du texte
    TexteBox textBox; // boîte de texte

public :
    /**
     * @brief Constructeur de la DataBox
     * @param score Valeur de DataBox
     * @param label Texte de la boîte de texte
     * @param glyphSize Taille de la police de texte
     * @param fontPath Chemin de la police de texte
     * @param position Position de la boîte de texte
     */
    DataBox(float _value, const char* _label, int glyphSize, const char *fontPath, Vector2f position);

    /*
     * @brief Destructeur de la classe DataBox
     * @note Est virtual parce que la classe surchage une méthode de BbopDrawable
     * @note Désalloue la police de texte allouée dans le constructeur
     */
    virtual ~DataBox();

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
     * @brief Modifie la valeur de DataBox
     * @param score Nouvelle valeur de DataBox
     * @note Met à jour la boîte de texte
     */
    void setValue(float _value);

    /**
     * @brief Retourne la valeur de DataBox
     */
    int getValue() const;

    /**
     * @brief Retourne la position de la boîte de texte
     */
    Vector2f getPosition();
};