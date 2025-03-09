#include "../include/menu.h"
#include <fstream>

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


Menu::Menu(GLFWwindow * _window) :
    window(_window),
    background(new Sprite("sprite/iu/menu.png")),
    current_button(nullptr),
    released(true),
    released_t(glfwGetTime()),
    quit(false)
{
    initMenuButtons();
    std::cout << "Menu initialisé" << std::endl;
}

void Menu::initMenuButtons()
{
    Button * button_start = new Button;
    Button * button_settings = new Button;
    Button * button_exit = new Button;

    initButton(button_start, "start", true, Vector2f(180, 185), button_settings, button_exit);
    initButton(button_settings, "settings", false, Vector2f(180, 185+135), button_exit, button_start);
    initButton(button_exit, "exit", false, Vector2f(180, 185+135*2), button_start, button_settings);

    current_button = button_start;
}

void Menu::Draw()
{
    scene.Use();

    scene.Draw(*background);
    
    Button * start = current_button;
    Button * temp = current_button;

    // fait une boucle entière (temp est déjà égal à start)
    do
    {
        scene.Draw(*temp->sprite);
        temp = temp->next; 
    }
    while (temp != start);

    scene.render();
}

menu_input Menu::naviguation()
{
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS))
    {
        return menu_up;
    }
    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
    {
        return menu_down;
    }
    if ((glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS))
    {
        return menu_select;
    }
    return menu_null;
}

Menu::~Menu()
{
    if (!current_button) return; // Si la liste est vide, rien à faire

    Button* start = current_button;
    Button* temp = nullptr;

    do 
    {
        temp = current_button->next; // Sauvegarde le prochain élément
        delete current_button; // Supprime le bouton actuel
        current_button = temp; // Passe au suivant
    } 
    while (current_button != start); // Continue tant qu'on n'a pas bouclé

    current_button = nullptr; // Assure que le pointeur est nul après la destruction
}

Button *  Menu::update()
{
    menu_input input = naviguation();

    if(glfwGetTime() - released_t > 0.2) released = true;

    if(released && input != menu_null)
    {
        bool activated = false;
        std::string texture_path;

        switch (input)
        {
            case menu_up :
                while (!activated)
                {
                    setButton(current_button);
                    current_button = current_button->previous;
                    setButton(current_button);

                    activated = true;
                }
                released = false;
                released_t = glfwGetTime();
                break;

            case menu_down :
                while (!activated)
                {
                    setButton(current_button);
                    current_button = current_button->next;
                    setButton(current_button);

                    activated = true;
                }
                released = false;
                released_t = glfwGetTime();
                break;

            case menu_select :
                released = false; 
                released_t = glfwGetTime();

                return current_button;
                break;

            default :
                break;
        }
    }

    else if (input == menu_null) released = true;

    return nullptr;
}

void Menu::setButton(Button *& button)
{
    std::string texture_path;
    if (button->on) texture_path = "sprite/iu/button/" + button->name + "/0.png";
    else texture_path = "sprite/iu/button/" + button->name + "/1.png";
    button->sprite->setTexture(texture_path.c_str());

    button->on = !button->on;
}

Button * Menu::getButton()
{
    return current_button;
}

bool Menu::halfTime()
{
    if (!released)
    {
        current_button->released_t = glfwGetTime();
        current_button->released = true;

        std::string path = "sprite/iu/button/" + current_button->name + "/2.png";
        current_button->sprite->setTexture(path.c_str());
        
        return false;
    }
    else if (glfwGetTime() - current_button->released_t > 0.3)
    {
        std::string path = "sprite/iu/button/" + current_button->name + "/1.png";
        current_button->sprite->setTexture(path.c_str());

        current_button->released = false;
        quit = false;

        return true;
    }
    return false;
}

bool Menu::quitMenu()
{
    if (naviguation() == 2) 
    {
        quit = true;
        return true;
    }
    else if (quit) return true;

    return false;
}

