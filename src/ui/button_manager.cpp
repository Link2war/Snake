#include "../../include/ui/button_manager.h"


ButtonManager::ButtonManager() :
    m_buttons(),
    m_currentIndex(0),
    m_selectTimestamp(0),
    m_canNavigate(true),
    m_moveTimestamp(0)
{
    Button::initTextures();

    m_buttons.reserve(3);
    m_buttons.push_back(std::make_unique<Button>(ButtonName::Play, ButtonState::On, Vector2f(180, BASE_Y)));
    m_buttons.push_back(std::make_unique<Button>(ButtonName::Settings, ButtonState::Off, Vector2f(180, BASE_Y + SPACING)));
    m_buttons.push_back(std::make_unique<Button>(ButtonName::Exit, ButtonState::Off, Vector2f(180, BASE_Y + SPACING * 2)));
}

void ButtonManager::Draw(GLint* renderUniform) const
{
    for (const auto& b : m_buttons) {
        b->Draw(renderUniform);
    }
}

void ButtonManager::updateNavigateDelay(InputMenu input)
{
    if(glfwGetTime() - m_moveTimestamp > 0.2) {
        m_canNavigate = true;
    }
    else if (!m_canNavigate && input == InputMenu::Null) {
        m_canNavigate = true;
    }
}

void ButtonManager::processInput(InputMenu input)
{
    switch (input)
    {
        case InputMenu::Up :
            m_buttons[m_currentIndex]->desactivate();
            m_currentIndex = (m_currentIndex +  m_buttons.size() - 1) % m_buttons.size();
            m_buttons[m_currentIndex]->activate();

            m_canNavigate = false;
            m_moveTimestamp = glfwGetTime();
            break;

        case InputMenu::Down :
            m_buttons[m_currentIndex]->desactivate();
            m_currentIndex = (m_currentIndex + 1) % m_buttons.size();
            m_buttons[m_currentIndex]->activate();
            
            m_canNavigate = false;
            m_moveTimestamp = glfwGetTime();
            break;

        case InputMenu::Select :
            m_canNavigate = false; 
            m_moveTimestamp = glfwGetTime();
            if (m_buttons[m_currentIndex]->getState() != ButtonState::Select) { // évite de relancer le timer
                m_buttons[m_currentIndex]->select();
                m_selectTimestamp = glfwGetTime();
            }
            break;

        default :
            break;
    }
}

void ButtonManager::update(InputMenu input, float deltaTime)
{
    if (!m_canNavigate) {
        updateNavigateDelay(input);
    }

    if (m_canNavigate) {
        processInput(input);
    }
}

void ButtonManager::moveTo(Vector2f velocity, float deltaTime)
{
    for (const auto& b : m_buttons) {
        Vector2f pos = b->getPosition();
        b->setPosition(Vector2f(pos.x + velocity.x*deltaTime, pos.y + velocity.y*deltaTime));
    }
}

bool ButtonManager::selectTimestampOver()
{
    if (glfwGetTime() - m_selectTimestamp > 0.3)
    {
        m_buttons[m_currentIndex]->activate();
        return true;
    }
    return false;
}

bool ButtonManager::buttonSelected(ButtonName buttonName, InputMenu input) const
{
    return (input == InputMenu::Select && m_buttons[m_currentIndex]->getName() == buttonName);
}