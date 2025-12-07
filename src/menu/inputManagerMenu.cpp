#include "../../include/menu/inputManagerMenu.h"

InputManagerMenu::InputManagerMenu() :
    input(InputMenu::Null)
{
    std::cout << "InputManagerMenu initialisé" << std::endl;
}

InputManagerMenu::~InputManagerMenu()
{
    std::cout << "InputManagerMenu supprimé" << std::endl;
}

void InputManagerMenu::update(GLFWwindow * window)
{
    input = InputMenu::Null;

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        input = InputMenu::Up;
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        input = InputMenu::Down;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        input = InputMenu::Select;
    }
}

InputMenu InputManagerMenu::getInput()
{
    return input;
}

void InputManagerMenu::reset()
{
    input = InputMenu::Null;
}