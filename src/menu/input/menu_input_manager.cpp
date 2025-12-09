#include "../../../include/menu/input/menu_input_manager.h"

MenuInputManager::MenuInputManager() :
    m_input(InputMenu::Null)
{
    std::cout << "MenuInputManager initialisé" << std::endl;
}

MenuInputManager::~MenuInputManager()
{
    std::cout << "MenuInputManager supprimé" << std::endl;
}

void MenuInputManager::update(GLFWwindow * window)
{
    m_input = InputMenu::Null;

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        m_input = InputMenu::Up;
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        m_input = InputMenu::Down;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        m_input = InputMenu::Select;
    }
}

InputMenu MenuInputManager::getInput()
{
    return m_input;
}

void MenuInputManager::reset()
{
    m_input = InputMenu::Null;
}