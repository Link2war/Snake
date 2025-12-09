#pragma once

#include <BBOP/Graphics.h>
#include <memory>

/**
 * @brief Noms des différents boutons du jeu
 * @note Il n'existe qu'un Button de chaque nom différent
 */
enum class ButtonName
{
    Play = 0,
    Settings = 1,
    Exit = 2
};

/**
 * @brief Etats d'un Button
 * @note Chaque etat sert d'animation
 */
enum class ButtonState
{
    Off = 0,
    On = 1,
    Select = 2
};

/**
 * @brief Stocke le nom des Button en char*
 */
extern const char* buttonName[];

/**
 * @brief Transforme le nom du bouton ButtonName en String
 * @note Sert au chemin de la texture
 */
std::string to_string(ButtonName name);

/**
 * @brief Bouton de jeu
 * @note possède un pointeur vers le bouton suivant
 */
class Button : public BbopDrawable
{
private :
    static std::unique_ptr<Texture> m_textures[3][3]; // textures[name][state]

    ButtonName m_name; // nom du bouton
    ButtonState m_state; // etat du bouton (activé / désactivé)
    Sprite m_sprite; // sprite du bouton

public :
    /**
     * @brief Constructeur de la classe Button
     * @param name Nom du Button
     * @param state Etat du Button
     * @param position Position du Button
     */
    Button(ButtonName name, ButtonState state, Vector2f position);

    /**
     * @brief Destructeur de la classe Button
     * @note Est virtual parce que la classe surcharge la méthode Draw héritée de BbopDrawable
     */
    virtual ~Button() = default;

    /**
     * @brief Affichage du Sprite sur l'écran
     * @note Méthode surchargée de BbopDrawable
     */
    void Draw(GLint* renderUniform) const override;

    /**
     * @brief Initialise toutes les textures de Button
     * @note Stocke les textures chargées dans la variable textures
     */
    static void initTextures();

    /**
     * @brief Modifie la position du Sprite
     * @param position Nouvelle position du Sprite
     */
    void setPosition(Vector2f position);

    /**
     * @brief Change l'état du Button en On
     * @note Change la texture du Sprite
     */
    void activate();

    /**
     * @brief Change l'état du Button en Off
     * @note Change la texture du Sprite
     */
    void desactivate();

    /**
     * @brief Change l'état du Button en Select
     * @note Change la texture du Sprite
     */
    void select();

    /**
     * @brief Retourne la position du Sprite
     */
    Vector2f getPosition() const;

    /**
     * @brief Retourne l'etat du Button
     */
    ButtonState getState() const;

    /**
     * @brief Retourne le nom du Button
     */
    ButtonName getName() const;
};