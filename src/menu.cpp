#include "../include/menu.h"
#include <fstream>

Menu::Menu(GLFWwindow * _window) :
    window(_window),
    background(new Sprite("sprite/iu/menu.png")),
    released(true),
    released_t(glfwGetTime()),
    current_button(nullptr)
{
    std::ifstream filename("info_button.txt");
    std::string info;

    if (!filename)
    {
        std::cout << "Erreur lors de l'ouverture du fichier " << std::endl;
        exit(1);
    }
    else
    {
        filename >> info;

        while (info != "-")
        {
            Button * button = new Button; // nouveau bouton

            button->name = info; // nom

            filename >> info; // booléen on
            if (info == "true") button->on = true;
            else button->on = false;

            filename >> info; // chemin du sprite
            button->sprite = new Sprite(info.c_str());

            filename >> info; // position x
            float x = stoi(info);

            filename >> info; // position y
            float y = stoi(info);
            button->sprite->setPosition(x, y);

            filename >> info; // ligne suivante

            button->next = nullptr;
            button->previous = nullptr;


            // liste chaînée
            if (current_button == nullptr) current_button = button;
            else
            {
                Button * temp = current_button;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = button;
                button->previous = temp;
            }
        }   
    }
    filename.close();

    std::cout << "Menu initialisé" << std::endl;

    // pointeur du dernier bouton vers le premier et vice versa
    Button * temp = current_button;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = current_button;
    current_button->previous = temp; 
    temp = current_button;
}

void Menu::Draw(Scene scene)
{
    scene.Draw(*background);
    
    Button * start = current_button;
    Button * temp = current_button;

    do
    {
        scene.Draw(*temp->sprite);
        temp = temp->next; 
    }
    while (temp != start);
}

menu_input Menu::naviguation()
{
    if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        return menu_up;
    }
    if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        return menu_down;
    }
    if ((glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS))
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

    current_button = nullptr; // Assure-toi que le pointeur est nul après la destruction
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
    if (button->on)
    {
        button->on = false;
        texture_path = "sprite/iu/button/" + button->name + "_0.png";
    }
    else
    {
        button->on = true;
        texture_path = "sprite/iu/button/" + button->name + "_1.png";
    }
    button->sprite->setTexture(texture_path.c_str());
}