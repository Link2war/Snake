#include "../../include/ui/button.h"

std::unique_ptr<Texture> Button::m_textures[3][3];

const char* buttonName[] = {
    "play",
    "settings",
    "exit"
};

std::string to_string(ButtonName name)
{
    return buttonName[static_cast<int>(name)];
}

Button::Button(ButtonName name, ButtonState state, Vector2f position) :
    m_name(name),
    m_state(state),
    m_sprite(*m_textures[(int)name][(int)state], position)
{

}

void Button::initTextures()
{
    for (int n = 0; n < 3; n++)
    {
        std::string base = "assets/sprites/iu/button/" + to_string((ButtonName)n) + "/";

        m_textures[n][0] = std::make_unique<Texture>((base + "0.png").c_str());
        m_textures[n][1] = std::make_unique<Texture>((base + "1.png").c_str());
        m_textures[n][2] = std::make_unique<Texture>((base + "2.png").c_str());
    }
}

void Button::Draw(GLint* renderUniform) const
{
    m_sprite.Draw(renderUniform);
}

void Button::setPosition(Vector2f position)
{
    m_sprite.setPosition(position);
}

void Button::activate()
{
    m_state = ButtonState::On;
    m_sprite.setTexture(*m_textures[(int)m_name][(int)m_state]);
}

void Button::desactivate()
{
    m_state = ButtonState::Off;
    m_sprite.setTexture(*m_textures[(int)m_name][(int)m_state]);
}

void Button::select()
{
    m_state = ButtonState::Select;
    m_sprite.setTexture(*m_textures[(int)m_name][(int)m_state]);
}

Vector2f Button::getPosition() const
{
    return m_sprite.getPosition();
}

ButtonName Button::getName() const
{
    return m_name;
}

ButtonState Button::getState() const
{
    return m_state;
}