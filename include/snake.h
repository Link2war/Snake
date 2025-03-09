#pragma once

#include <BBOP/Graphics.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Block
{
    private :
        Sprite * sprite; // sprite du block
        float velocity; // vitesse du block
        std::string direction; // direction du block
        
        Vector2f initPos; // position initiale quand le block est sur une case
        Vector2f currentPos; // position actuelle du block
        Vector2f destPos; // position prévue de la prochaine case

        Block* next; // pointeur vers le block suivant (en direction de la queue)
        Block* previous; // pointeur vers le block précédent (en direction de la tête)

    public :

        friend class Snake;

        /* @brief constructeur de la classe Block
        @param texture chemin du sprite
        @param x abscisse du block
        @param y ordonnée du block
        @note ajoute un block queue pour avoir un Snake avec une tête et un corps */
        Block(Texture texture, float x, float y);

        /* @brief destructeur de la classe Block
        @note détruit les pointeurs de la classe */
        ~Block(); 

        // appelle la fonction move() à chaque frame
        void update(); 

        /* @brief Retourne true si le block est sur une case sinon retourne false
        @note Utilisé pour les changements de direction */
        bool onCell(); 

        /* @brief Déplacement du block vers le haut
        @note Met à jour la position 
        @note - position.y -= vitesse */
        void moveUp();

        /* @brief Déplacement du block vers le bas
        @note Met à jour la position 
        @note - position.y += vitesse */
        void moveDown(); 

        /* @brief Déplacement du block vers la gauche
        @note Met à jour la position 
        @note - position.x -= vitesse */
        void moveLeft(); 

        /* @brief Déplacement du block vers la droite
        @note Met à jour la position 
        @note - position.x += vitesse */
        void moveRight(); 

        // @brief mise à jour du déplacement
        void move();

        /* @brief met à jour la direction du block
        @param direction input de direction
        @note quand le block est sur une case :
        @note - Si le block correspond au block de la tête du Snake : 
        @note La direction dépend de la position de départ et d'arrivée du block.
        @note - Sinon : 
        @note La direction dépend de la position actuelle du block et de la position de départ du block tête. */
        void setDirection();

        /* @brief Change la case de depart du block
        @note La position de départ du block = position actuelle du block */
        void setInitPos();

        /* @brief Change la case d'arrivée du block
        @note La position d'arrivée du block = la position de départ du block tête */
        void setDestPos();

        /* @brief Modifie l'image du sprite
        @note Utilisé lorsque le Snake mange un block */
        void setSprite(Texture texure);

        /* @brief Retourne le sprite du block
        @note Récupéré par la classe Game pour afficher chaque block */ 
        Sprite * getSprite(); 

        // @brief Retourne la position actuelle du block (case actuelle / entre deux cases)
        Vector2f getCurrentPos(); 

        /* retourne la position (case) d'arrivée du block
        @note Utilisé dans la classe Game pour parcourir le Snake */
        Vector2f getDestPos();

        /* @brief Retourne le block suivant
        @note Utilisé dans la classe Game pour parcourir le Snake */
        Block * getNext();         
};

class Snake
{
    private :
        Vector2f defaultPos; // position du Snake en début de partie
        Block* head; // Pointeur vers le block de tête du Snake (premier block du Snake)
        Block* tail; // Pointeur vers le block queue du Snake (dernier block du Snake)

    public :
        /* @brief Constructeur de la classe Snake
        @note génère un Snake avec trois blocks
        @note - Un block pour la tête
        @note - Un block pour le corps
        @note - Un block pour la queue */
        Snake(float x, float y);

        /* @brief Destructeur de la classe Snake
        @note Désalloue tous les pointeurs de type Block */
        ~Snake();

        /* @brief Mise à jour de tous les blocks du Snake
        @param direction Input de direction transmis à la tête du Snake
        @note Mise à jour du block tête puis des autres blocks
        @note - Mise à jour block tête : direction, départ, arrviée, position
        @note -  Mise à jour des autres blocks : départ, arrivée, direction, position */
        void update(std::string direction);

        /* @brief Ajoute un nouveau block au Snake
        @note Si le Snake à déja une queue :
        @note - Modifie le sprite du block queue
        @note - Ajoute un nouveau block à la queue du Snake avec la position de départ de l'ancien block queue
        @note - Le pointeur du block queue devient celui du nouveau block queue */
        void addBlock();

        /* @brief Vérifie si le joueur est en dehors des limites de l'écran de jeu
        @param offsetX Offset x de l'écran de jeu
        @param offsetY Offset y de l'écran de jeu */
        bool OutOfBounds(float offsetX, float offsetY);

        // @brief Vérifie si le Snake s'est mordue la queue
        bool Hit();

        /* @brief Retourne le pointeur du block de tête du Snake 
        @note Récupéré par le Game */
        Block* getHead();

        /* @brief Change la direction du Snake (tête)
        @param direction input de direction à appliquer au Snake (tête) */
        void setDirection(std::string direction);

        /* @brief Change la position d'arrivée de la tête du Snake 
        @note Change la position d'arrivée selon la direction de la tête du Snake */
        void setDestPos(); 

        /* @brief Retourne la direction du Snake
        @note utilisé par la gestion d'input de déplacement dans le Game */
        std::string getDirection();
};