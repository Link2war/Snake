#include "../include/menu.h"

Menu::Menu() :
    background(new Sprite("sprite/iu/menu.png")),
    start_buton(new Sprite("sprite/iu/buton/start_buton2.png")),
    settings_buton(new Sprite("sprite/iu/buton/settings_buton1.png")),
    on_start(true),
    on_settings(false),
    start(false)
{
    float x = background->getSize().x;
    float y = background->getSize().y;
    start_buton->setPosition(x/2 - start_buton->getSize().x/2, y/2.5);
    settings_buton->setPosition(x/2 - start_buton->getSize().x/2, y/1.5);

    std::cout << "menu" << std::endl;
}

void Menu::Draw(Scene scene)
{
    scene.Draw(*background);
    scene.Draw(*start_buton);
    scene.Draw(*settings_buton);
}

void Menu::checkStart(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && on_start == true) start = true;
}

bool Menu::pressStart()
{
    return start;
}

void Menu::onStart(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && on_start == false) 
    {
        on_start = !on_start;
        on_settings = !on_settings;
        start_buton->setTexture("sprite/iu/buton/start_buton2.png");
        settings_buton->setTexture("sprite/iu/buton/settings_buton1.png");
    }
}

void Menu::onSettings(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && on_settings == false) 
    {
        on_start = !on_start;
        on_settings = !on_settings;
        settings_buton->setTexture("sprite/iu/buton/settings_buton2.png");
        start_buton->setTexture("sprite/iu/buton/start_buton1.png");
    }
}

void Menu::reset()
{
    start_buton->setTexture("sprite/iu/buton/start_buton2.png");
    settings_buton->setTexture("sprite/iu/buton/settings_buton1.png");
    on_start = true;
    on_settings = false;
    start = false;
}