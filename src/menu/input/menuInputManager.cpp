#include "../../../include/menu/input/menuInputManager.h"

MenuInputManager::MenuInputManager() :
    input(InputMenu::Null)
{
    std::cout << "MenuInputManager initialisé" << std::endl;
}

MenuInputManager::~MenuInputManager()
{
    std::cout << "MenuInputManager supprimé" << std::endl;
}

void MenuInputManager::update(GLFWwindow * window)
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

InputMenu MenuInputManager::getInput()
{
    return input;
}

void MenuInputManager::reset()
{
    input = InputMenu::Null;
}