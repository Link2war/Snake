#include "../include/menu.h"
#include <fstream>


Menu::Menu(GLFWwindow * _window) :
    window(_window),
    board(new Sprite("sprite/iu/board.png")),
    currentButton(nullptr),
    released(true),
    released_t(glfwGetTime()),
    quit(false),
    enter(false),
    speedTransition(8)
{
    initMenuButtons();
    std::cout << "Menu initialisé" << std::endl;
}

void Menu::Draw()
{
    scene.Use();

    scene.Draw(*board);
    
    Button * start = currentButton;
    Button * temp = currentButton;

    // fait une boucle entière (temp est déjà égal à start)
    do
    {
        scene.Draw(*temp->sprite);
        temp = temp->next; 
    }
    while (temp != start);

    scene.render();
}

menu_input Menu::navigation()
{
    if (quit || enter)
    {
        return menu_null;
    }
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
    if (!currentButton) return; // Si la liste est vide, rien à faire

    Button* start = currentButton;
    Button* temp = nullptr;

    do 
    {
        temp = currentButton->next; // Sauvegarde le prochain élément
        delete currentButton; // Supprime le bouton actuel
        currentButton = temp; // Passe au suivant
    } 
    while (currentButton != start); // Continue tant qu'on n'a pas bouclé

    currentButton = nullptr; // Assure que le pointeur est nul après la destruction
}

Button *  Menu::update()
{
    menu_input input = navigation();

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
                    setButton(currentButton);
                    currentButton = currentButton->previous;
                    setButton(currentButton);

                    activated = true;
                }
                released = false;
                released_t = glfwGetTime();
                break;

            case menu_down :
                while (!activated)
                {
                    setButton(currentButton);
                    currentButton = currentButton->next;
                    setButton(currentButton);

                    activated = true;
                }
                released = false;
                released_t = glfwGetTime();
                break;

            case menu_select :
                released = false; 
                released_t = glfwGetTime();

                return currentButton;
                break;

            default :
                break;
        }
    }

    else if (input == menu_null) released = true;

    return nullptr;
}

void Menu::initMenuButtons()
{
    Button * button_start = new Button;
    Button * button_settings = new Button;
    Button * button_exit = new Button;

    initButton(button_start, "play", true, Vector2f(180, 185), button_settings, button_exit);
    initButton(button_settings, "settings", false, Vector2f(180, 185+135), button_exit, button_start);
    initButton(button_exit, "exit", false, Vector2f(180, 185+135*2), button_start, button_settings);

    currentButton = button_start;
}

void Menu::setButton(Button *& button)
{
    std::string texture_path;
    if (button->on) texture_path = "sprite/iu/button/" + button->name + "/0.png";
    else texture_path = "sprite/iu/button/" + button->name + "/1.png";
    button->sprite->setTexture(texture_path.c_str());

    button->on = !button->on;
}

std::string Menu::getButtonName()
{
    return currentButton->name;
}

bool Menu::halfTime()
{
    if (!currentButton->released)
    {
        currentButton->released_t = glfwGetTime();
        currentButton->released = true;

        std::string path = "sprite/iu/button/" + currentButton->name + "/2.png";
        currentButton->sprite->setTexture(path.c_str());
        
        return false;
    }
    else if (glfwGetTime() - currentButton->released_t > 0.3)
    {
        std::string path = "sprite/iu/button/" + currentButton->name + "/1.png";
        currentButton->sprite->setTexture(path.c_str());

        return true;
    }
    return false;
}

bool Menu::quitMenu()
{
    if (navigation() == 2) 
    {
        quit = true;
        return true;
    }
    else if (quit) return true;

    return false;
}

bool Menu::enterMenu()
{
    if (board->getPosition().y < 0) 
    {
        enter = true;
        return true;
    }
    else return false;
}

bool Menu::transitionOut()
{
    Vector2f boardPos = board->getPosition();
    if (boardPos.y > - board->getSize().y) 
    {
        // déplace tous les éléments de la scène
        board->setPosition(boardPos.x, boardPos.y - speedTransition);

        Button * start = currentButton;
        Button * temp = currentButton;
        do
        {
            Vector2f buttonPos = temp->sprite->getPosition();
            temp->sprite->setPosition(buttonPos.x, buttonPos.y - speedTransition);
            temp = temp->next; 
        }
        while (temp != start);

        return false; // état de la transition
    }
    else
    {
        // reset
        currentButton->released = false;
        quit = false;

        return true; // état de la transition (terminé)
    }
}

bool Menu::transitionIn()
{
    Vector2f boardPos = board->getPosition();
    board->setPosition(boardPos.x, boardPos.y + speedTransition);

    Button * start = currentButton;
    Button * temp = currentButton;
    do
    {
        Vector2f buttonPos = temp->sprite->getPosition();
        temp->sprite->setPosition(buttonPos.x, buttonPos.y + speedTransition);
        temp = temp->next; 
    }
    while (temp != start);

    // état de la transition
    if (board->getPosition().y < 0) return false;
    else 
    {
        enter = false;
        return true;
    }

}