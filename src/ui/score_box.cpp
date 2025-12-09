#include "../../include/ui/score_box.h"

ScoreBox::ScoreBox(int value, const char* label, int glyphSize, const char *fontPath, Vector2f position) :
    m_value(value),
    m_label(label),
    m_font(new Font(glyphSize, fontPath)),
    m_textBox(m_label, m_font)
{
    m_textBox.setColor(Vector3i(0, 0, 0));
    m_textBox.setPosition(position);
    updateTextBox();
}

ScoreBox::~ScoreBox()
{
    delete m_font;
    m_font = nullptr;
}

void ScoreBox::Draw(GLint* renderUniform) const
{
    m_textBox.Draw(renderUniform);
}

void ScoreBox::updateTextBox()
{
    std::string text = std::string(m_label) + std::to_string(m_value);
    m_textBox.setTexte(text.c_str());
}

void ScoreBox::setPosition(Vector2f position)
{
    m_textBox.setPosition(position);
}

void ScoreBox::setValue(float value)
{
    m_value = value;
    updateTextBox();
}

int ScoreBox::getValue() const
{
    return m_value;
}

Vector2f ScoreBox::getPosition()
{
    return m_textBox.getPosition();
}