#include "../../../include/core/input/input_manager.h"

InputManager::InputManager() :
    m_input(Vector2i(0, 0))
{
    std::cout << "InputManager initialisé" << std::endl;
}

InputManager::~InputManager()
{
    std::cout << "InputManager supprimé" << std::endl;
}

void InputManager::update(GLFWwindow * window)
{
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        m_input.x = 0;
        m_input.y = -1;
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        m_input.x = 0;
        m_input.y = 1;
    }
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
    {
        m_input.x = -1;
        m_input.y = 0;
    }
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
    {
        m_input.x = 1;
        m_input.y = 0;
    }
}

Vector2i InputManager::getInput()
{
    return m_input;
}