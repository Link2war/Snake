#pragma once 

#include <BBOP/Graphics.h>
#include "button.h"
#include <memory>

/**
 * @brief Les différents inputs du menu
 */
#ifndef INPUT_MENU
#define INPUT_MENU
enum class InputMenu
{
    Up = 0,
    Down = 1,
    Select = 2,
    Null = 3
};
#endif

class ButtonManager : public BbopDrawable
{
private :
    static constexpr float BASE_X = 180.0f;
    static constexpr float BASE_Y = 185.0f;
    static constexpr float SPACING = 135.0f;

    std::vector<std::unique_ptr<Button>> buttons; // stocke les différents Button du Menu
    int currentIndex; // index du Button actuel

    float selectTimestamp; // timestamp du dernier select
    bool canNavigate; // si on peut passer d'un Button à un autre
    float moveTimestamp; // timestamp du dernier changement de bouton

public :
    /**
     * @brief Constructeur de la classe ButtonManager
     * @note Initialise toutes les textures des différents Button
     */
    ButtonManager();

    /**
     * @brief Destructeur de la classe ButtonManager
     * @note Est virtual parce que la classe surcharge une méthode de BbopDrawable
     */
    virtual ~ButtonManager() = default;

    /**
     * @brief Affichage de tous les Button sur l'écran
     * @note Méthode surchargée de BbopDrawable
     */
    void Draw(GLint* renderUniform) const override;

    /**
     * @brief Met à jour la  variable canNavigate
     * @param input Input du Menu
     */
    void updateNavigateDelay(InputMenu input);

    /**
     * @brief Met à jour le bouton survolé et la sélection
     * @param input Input du Menu
     */
    void processInput(InputMenu input);

    /**
     * @brief Met à jour le delai de navigation et le processus de l'input
     */
    void update(InputMenu input, float deltaTime);

    /**
     * @brief Déplace tous les Button 
     * @param velocity vitesse de déplacement dans une direction précise
     * @note ajoute la velocity à la position
     */
    void moveTo(Vector2f velocity, float deltaTime);

    /**
     * @brief Laps de temps après avoir selectionné un bouton
     * @return retourne true si le laps de temps est terminé
     * @brief Remet le Button actuel en On
     */
    bool selectTimestampOver();

    /**
     * @brief Retourne true si le bouton survolé est selectionné
     */
    bool buttonSelected(ButtonName buttonName, InputMenu input) const;
};