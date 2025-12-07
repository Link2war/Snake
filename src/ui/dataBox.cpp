#include "../../include/ui/dataBox.h"

DataBox::DataBox(float _value, const char* _label, int glyphSize, const char *fontPath, Vector2f position) :
    value(_value),
    label(_label),
    font(new Font(glyphSize, fontPath)),
    textBox(_label, font)
{
    textBox.setColor(Vector3i(0, 0, 0));
    textBox.setPosition(position);
    updateTextBox();
}

DataBox::~DataBox()
{
    delete font;
    font = nullptr;
}

void DataBox::Draw(GLint* renderUniform) const
{
    textBox.Draw(renderUniform);
}

void DataBox::updateTextBox()
{
    std::string text = std::string(label) + std::to_string(value);
    textBox.setTexte(text.c_str());
}

void DataBox::setPosition(Vector2f position)
{
    textBox.setPosition(position);
}

void DataBox::setValue(float _value)
{
    value = _value;
    updateTextBox();
}

int DataBox::getValue() const
{
    return value;
}

Vector2f DataBox::getPosition()
{
    return textBox.getPosition();
}