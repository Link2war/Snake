#include "../include/iu.h"

void initButton(Button *& button, const char * name, bool on, Vector2f position, Button * next, Button * previous)
{
    std::string texture_path;

    button->name = name;
    button->on = on;
    button->released = false;
    button->released_t = glfwGetTime();
    
    if (on) texture_path = "sprite/iu/button/" + button->name + "/1.png";
    else texture_path = "sprite/iu/button/" + button->name + "/0.png";
    button->sprite = new Sprite(texture_path.c_str());
    button->sprite->setPosition(position);

    button->next = next;
    button->previous = previous;
}