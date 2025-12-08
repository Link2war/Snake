#pragma once

#include <BBOP/Graphics.h>
#include <memory>


/**
 * @brief Parties du corps du Snake
 */
enum class BodyPart
{
    Head,
    Body,
    Tail
};


class SnakeSegment : public BbopDrawable
{
private :
    static std::unique_ptr<Texture> textures[3]; // textures[BodyPart]

    Sprite sprite; // sprite du block
    float speed; // vitesse du block
    Vector2i direction; // direction du block
    Vector2f startPosition; // position initiale quand le block est sur une case
    Vector2f currentPosition; // position actuelle du block
    Vector2f targetPosition; // position prévue de la prochaine case

public :
    /**
     * @brief Constructeur de la classe Block
     * @param texture texture du sprite
     * @param position position initiale du snake
     */
    SnakeSegment(BodyPart bodyPart, Vector2f position);

    /**
     * @brief Destructeur de la classe Block
     * @note Est virtual parce que la méthode Draw est surchargée
     */
    virtual ~SnakeSegment(); 

    /**
     * @brief Charge les textures des différentes parties du corps du Snake
     */
    static void initTextures();

    /**
     * @brief Surcharge de la méthode Draw de BbopDrawable
     * @note Permet de dessiner l'objet Block plutôt que de dessiner l'objet Sprite
     */
    virtual void Draw(GLint* renderUniform) const override;

    /**
     * @brief Mise à jour du Block
     * @note Mise à jour :
     * @note - des différentes positions du Block
     * @note - de la position du Sprite
     */
    void update(float deltaTime); 

    /**
     * @brief Met à jour la rotation du Block
     */
    void updateRotation();

    /**
     * @brief Mise à jour de déplacement
     */
    void updateCurrentPosition(float deltaTime);

    /**
     * @brief Met à jour la case de départ du Block
     * @note La position de départ du block = position actuelle du block sur les frames OnCell()
     */
    void updateStartPosition();

    /**
     * @brief Met à jour la position d'arrivée
     * @note Dépend de la position de départ et de la direction
     * @note ! startPosition doit être mis à jour avant
     */
    void updateTargetPosition();

    /**
     * @brief Modifie la direction avec celle en paramètre
     */
    void setDirection(Vector2i _direction);

    /**
     * @brief Modifie la texture du Sprite avec celle en paramètre
     */
    void setTexture(BodyPart bodyPart);

    /**
     * @brief Vérifie si le Block est sur une case
     * @return Renvoie False si le Block est entre deux cases
     * @note Une case fait 32x32 pixels
     */
    bool onCell() const; 

    /**
     * @brief Retourne la position de départ
     */
    Vector2f getStartPosition() const;

    /**
     * @brief Retourne la position actuelle
     */
    Vector2f getCurrentPosition() const; 

    /**
     * @brief Retourne la position d'arrivée
     */
    Vector2f getTargetPosition() const; 

    /**
     * @brief Retourne la direction du Block
     */
    Vector2i getDirection() const;
};