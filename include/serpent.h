#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Bbop-Library/include/BBOP/Graphics.h"

class Block
{
    private :
        Sprite * sprite; // sprite du block
        float vitesse; // vitesse du block
        std::string direction; // direction du block
        
        Vector2f depart; // position initiale quand le block est sur une case
        Vector2f position; // position actuelle du block
        Vector2f arrivee; // position prévue de la prochaine case

        Block* suivant; // pointeur vers le block suivant (en direction de la queue)
        Block* precedent; // pointeur vers le block précédent (en direction de la tête)

        int frame; // frame animation du sprite

    public :

        friend class Serpent;

        /* @brief constructeur de la classe Block
        @param texture chemin du sprite
        @param x abscisse du block
        @param y ordonnée du block
        @note ajoute un block queue pour avoir un serpent avec une tête et un corps */
        Block(Texture texture, float x, float y);

        /* @brief destructeur de la classe Block
        @note détruit les pointeurs de la classe */
        ~Block(); 

        // appelle la fonction move() à chaque frame
        void update(); 

        /* @brief Retourne true si le block est sur une case sinon retourne false
        @note Utilisé pour les changements de direction */
        bool onCase(); 

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
        @note - Si le block correspond au block de la tête du serpent : 
        @note La direction dépend de la position de départ et d'arrivée du block.
        @note - Sinon : 
        @note La direction dépend de la position actuelle du block et de la position de départ du block tête. */
        void setDirection();

        /* @brief Change la case de depart du block
        @note La position de départ du block = position actuelle du block */
        void setDepart();

        /* @brief Change la case d'arrivée du block
        @note La position d'arrivée du block = la position de départ du block tête */
        void setArrivee();

        /* @brief Modifie l'image du sprite
        @note Utilisé lorsque le serpent mange un block */
        void setSprite(Texture texure);

        /* @brief Retourne le sprite du block
        @note Récupéré par la classe Game pour afficher chaque block */ 
        Sprite * getSprite(); 

        // @brief Retourne la position actuelle du block (case actuelle / entre deux cases)
        Vector2f getPosition(); 

        /* @brief Retourne le block suivant
        @note Utilisé dans la classe Game pour parcourir le serpent */
        Block * getSuivant(); 

        /* retourne la position (case) d'arrivée du block
        @note Utilisé dans la classe Game pour parcourir le serpent */
        Vector2f getArrivee();
        
};

class Serpent
{
    private :
        Vector2f position_defaut; // position du serpent en début de partie
        Block* tete; // Pointeur vers le block de tête du serpent (premier block du serpent)
        Block* queue; // Pointeur vers le block queue du serpent (dernier block du serpent)

    public :
        /* @brief Constructeur de la classe Serpent
        @note génère un serpent avec trois blocks
        @note - Un block pour la tête
        @note - Un block pour le corps
        @note - Un block pour la queue */
        Serpent(float x, float y);

        /* @brief Destructeur de la classe Serpent
        @note Désalloue tous les pointeurs de type Block */
        ~Serpent();

        /* @brief Mise à jour de tous les blocks du serpent
        @param direction Input de direction transmis à la tête du serpent
        @note Mise à jour du block tête puis des autres blocks
        @note - Mise à jour block tête : direction, départ, arrviée, position
        @note -  Mise à jour des autres blocks : départ, arrivée, direction, position */
        void update(std::string direction);

        /* @brief Ajoute un nouveau block au serpent
        @note Si le serpent à déja une queue :
        @note - Modifie le sprite du block queue
        @note - Ajoute un nouveau block à la queue du serpent avec la position de départ de l'ancien block queue
        @note - Le pointeur du block queue devient celui du nouveau block queue */
        void addBlock();

        /* @brief Vérifie si le joueur est en dehors des limites de l'écran de jeu
        @param offsetX Offset x de l'écran de jeu
        @param offsetY Offset y de l'écran de jeu */
        bool OutOfBounds(float offsetX, float offsetY);

        // @brief Vérifie si le serpent s'est mordue la queue
        bool Hit();

        /* @brief Retourne le pointeur du block de tête du serpent 
        @note Récupéré par le Game */
        Block* getTete();

        /* @brief Change la direction du serpent (tête)
        @param direction input de direction à appliquer au serpent (tête) */
        void setDirection(std::string direction);

        /* @brief Change la position d'arrivée de la tête du serpent 
        @note Change la position d'arrivée selon la direction de la tête du serpent */
        void setArrivee(); 

        /* @brief Retourne la direction du serpent
        @note utilisé par la gestion d'input de déplacement dans le Game */
        std::string getDirection();
};