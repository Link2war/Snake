#include "../../include/ui/buttonManager.h"


ButtonManager::ButtonManager() :
    buttons(),
    currentIndex(0),
    selectTimestamp(0),
    canNavigate(true),
    moveTimestamp(0)
{
    Button::initTextures();

    buttons.reserve(3);
    buttons.push_back(std::make_unique<Button>(ButtonName::Play, ButtonState::On, Vector2f(180, BASE_Y)));
    buttons.push_back(std::make_unique<Button>(ButtonName::Settings, ButtonState::Off, Vector2f(180, BASE_Y + SPACING)));
    buttons.push_back(std::make_unique<Button>(ButtonName::Exit, ButtonState::Off, Vector2f(180, BASE_Y + SPACING * 2)));
}

void ButtonManager::Draw(GLint* renderUniform) const
{
    for (const auto& b : buttons) {
        b->Draw(renderUniform);
    }
}

void ButtonManager::updateNavigateDelay(InputMenu input)
{
    if(glfwGetTime() - moveTimestamp > 0.2) {
        canNavigate = true;
    }
    else if (!canNavigate && input == InputMenu::Null) {
        canNavigate = true;
    }
}

void ButtonManager::processInput(InputMenu input)
{
    switch (input)
    {
        case InputMenu::Up :
            buttons[currentIndex]->desactivate();
            currentIndex = (currentIndex +  buttons.size() - 1) % buttons.size();
            buttons[currentIndex]->activate();

            canNavigate = false;
            moveTimestamp = glfwGetTime();
            break;

        case InputMenu::Down :
            buttons[currentIndex]->desactivate();
            currentIndex = (currentIndex + 1) % buttons.size();
            buttons[currentIndex]->activate();
            
            canNavigate = false;
            moveTimestamp = glfwGetTime();
            break;

        case InputMenu::Select :
            canNavigate = false; 
            moveTimestamp = glfwGetTime();
            if (buttons[currentIndex]->getState() != ButtonState::Select) { // évite de relancer le timer
                buttons[currentIndex]->select();
                selectTimestamp = glfwGetTime();
            }
            break;

        default :
            break;
    }
}

void ButtonManager::update(InputMenu input)
{
    if (!canNavigate) {
        updateNavigateDelay(input);
    }

    if (canNavigate) {
        processInput(input);
    }
}

void ButtonManager::moveTo(Vector2f velocity)
{
    for (const auto& b : buttons) {
        Vector2f pos = b->getPosition();
        b->setPosition(Vector2f(pos.x + velocity.x, pos.y + velocity.y));
    }
}

bool ButtonManager::selectTimestampOver()
{
    if (glfwGetTime() - selectTimestamp > 0.3)
    {
        buttons[currentIndex]->activate();
        return true;
    }
    return false;
}

bool ButtonManager::buttonSelected(ButtonName buttonName, InputMenu input) const
{
    return (input == InputMenu::Select && buttons[currentIndex]->getName() == buttonName);
}