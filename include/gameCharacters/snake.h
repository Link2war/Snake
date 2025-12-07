#pragma once

#include <BBOP/Graphics.h>
#include "block.h"
#include <deque>


class Snake : public BbopDrawable
{
    private :
        std::deque<Block> body; // tableau de Block
        Vector2f initPosition; // position initiale du Snake (utilisé pour le reset)

    public :
        /**
         * @brief Constructeur de la classe Snake
         * @param position Position initiale du Snake
         * @note Génère 3 Blocks :
         * @note - 1 Block pour la tête
         * @note - 1 Block pour le corps
         * @note - 1 Block pour la queue
         */
        Snake(Vector2f position);

        /**
         * @brief Destructeur de la classe Snake
         * @note Est virtual parce que la fonction Draw est surchargée
         */
        virtual ~Snake();

        /**
         * @brief Initialise le Snake
         * @note - Initialise la tête
         * @note - Initialise le corps
         * @note - Initialise la queue
         */
        void initBody();

        /**
         * @brief Reset du Snake
         * @note Supprime les blocks du Snake
         * @note Initialise de nouveaux blocks pour le Snake
         */
        void reset();

        /**
         * @brief Surcharge de la méthode Draw de BbopDrawable
         * @note Permet de dessiner l'objet Snake (ensemble de Block) plutôt que de dessiner l'objet Sprite (de chaque Block)
         */
        virtual void Draw(GLint* renderUniform) const override;

        /**
         * @brief Mise à jour du Snake
         * @note - direction
         * @note - les différentes positions de chaque Block
         * @note - déplace chaque block
         */
        void update(Vector2i inputDirection);

        /**
         * @brief Met à jour la direction du Block de tête
         * @param inputDirection input de la direction du Snake
         */
        void updateFrontDirection(Vector2i inputDirection);

        /**
         * @brief Met à jour tous les Block du Snake
         * @note - Met à jour les positions du Block de la tête du Snake
         * @note - Met à jour la direction puis les positions de chaque Block du reste du Snake
         */
        void updateBlocksBody();

        /**
         * @brief Ajout d'un Block au Snake
         * @note Le Sprite de la queue du Snake change
         */
        void addBlock();

        /**
         * @brief Vérifie si le joueur est en dehors des limites de l'écran de jeu
         * @param offsetX Offset x de l'écran de jeu
         * @param offsetY Offset y de l'écran de jeu
         */
        bool isOutOfBounds(float offsetX, float offsetY);

        /**
         * @brief Vérifie si le Snake s'est mordue la queue
         */
        bool isBittingBody();

        /**
         * @brief Vérifie si le snake est en collision avec un autre objet de Game
         * @param position Position de l'objet
         * @note Retourne true si les positions d'un des Block du Snake est la même que celle en paramètre
         */
        bool collideFruit(Vector2f fruitPosition);

        /**
         * @brief Vérifie si le snake est mort
         * @param offsetX offset x du plateau de jeu
         * @param offsetY offset y du plateau de jeu
         * @note Retourne true si le snake se mord ou s'heurtre à une paroi
         */
        bool isDead(float offsetX, float offsetY);
};