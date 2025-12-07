#include "../../include/ui/button.h"

std::unique_ptr<Texture> Button::textures[3][3];

const char* buttonName[] = {
    "play",
    "settings",
    "exit"
};

std::string to_string(ButtonName name)
{
    return buttonName[static_cast<int>(name)];
}

Button::Button(ButtonName _name, ButtonState _state, Vector2f position) :
    name(_name),
    state(_state),
    sprite(*textures[(int)name][(int)state], position)
{

}

void Button::initTextures()
{
    for (int n = 0; n < 3; n++)
    {
        std::string base = "assets/sprites/iu/button/" + to_string((ButtonName)n) + "/";

        textures[n][0] = std::make_unique<Texture>((base + "0.png").c_str());
        textures[n][1] = std::make_unique<Texture>((base + "1.png").c_str());
        textures[n][2] = std::make_unique<Texture>((base + "2.png").c_str());
    }
}

void Button::Draw(GLint* renderUniform) const
{
    sprite.Draw(renderUniform);
}

void Button::setPosition(Vector2f position)
{
    sprite.setPosition(position);
}

void Button::activate()
{
    state = ButtonState::On;
    sprite.setTexture(*textures[(int)name][(int)state]);
}

void Button::desactivate()
{
    state = ButtonState::Off;
    sprite.setTexture(*textures[(int)name][(int)state]);
}

void Button::select()
{
    state = ButtonState::Select;
    sprite.setTexture(*textures[(int)name][(int)state]);
}

Vector2f Button::getPosition() const
{
    return sprite.getPosition();
}

ButtonName Button::getName() const
{
    return name;
}

ButtonState Button::getState() const
{
    return state;
}