#pragma once

#include <BBOP/Graphics.h>

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string>


struct Button
{
    std::string name;
    bool on;
    bool released; // si le bouton a été sélectionné
    double released_t; // timing depuis que le bouton a été selectionné

    Sprite * sprite;
    Button * next;
    Button * previous;
};

/* @brief constructeur d'un Button
@note Prend un Button en argument, lui attribut les autres valeurs mises en arguments
*/
void initButton(Button *& button, const char * name, bool on, Vector2f position, Button * next, Button * previous);