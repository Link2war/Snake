#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>


class Block
{
    private :
        Sprite * sprite; // sprite du block
        float vitesse; // vitesse du block

        // deplacement
        Vector2f position_depart; // position initiale quand le block est sur une case
        Vector2f position_actuelle; // position du block
        Vector2f position_arrivee; // position prévue de la prochaine case

        // direction
        std::string direction;

    public :
        Block(float x, float y); //constructeur de la classe Block
        ~Block(); // destructeur de la classe Block

        // appelé par l'update de la classe Game
        void update(); // mise a jour du deplacement du sprite

        // deplacement
        void moveUp(); // deplacement vers le haut
        void moveDown(); // deplacement vers le bas
        void moveLeft(); // deplacement vers la gauche
        void moveRight(); // deplacement vers la droite
        void move(); // deplacement generale, fait appel aux autres fonctions move

        // modifier par la classe Game
        void setDirection(Block * block);
        void setPositionDepart(Vector2f position); // change la position de depart du block
        void setPositionActuelle(Vector2f position); // change la position actuelle du block
        void setPositionArrivee(Vector2f position); // change la position d'arrivée du block
        void setPositionTete(std::string direction_); // change la position d'arrivée du block tête

        // recuperer par la classe Game
        Sprite * getSprite(); // retourne le sprite du block
        std::string getDirection();
        Vector2f getPositionDepart(); // retourne la position de depart du block (case initiale)
        Vector2f getPositionActuelle(); // retourne la position actuelle du block (case actuelle / entre deux cases)
        Vector2f getPositionArrivee(); // retourne la position d'arrivee du block (la prochaine case)
        bool onCase(); // retourne true si le block est sur une case sinon retourne false
};