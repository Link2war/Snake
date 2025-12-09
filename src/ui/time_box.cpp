#include "../../include/ui/time_box.h"

TimeBox::TimeBox(const char* label, int glyphSize, const char *fontPath, Vector2f position) :
    m_seconds(0),
    m_minutes(0),
    m_hours(0),
    m_label(label),
    m_font(new Font(glyphSize, fontPath)),
    m_textBox(m_label, m_font)
{
    m_textBox.setColor(Vector3i(0, 0, 0));
    m_textBox.setPosition(position);
    updateTextBox();
}

TimeBox::~TimeBox()
{
    delete m_font;
    m_font = nullptr;
}

void TimeBox::Draw(GLint* renderUniform) const
{
    m_textBox.Draw(renderUniform);
}

void TimeBox::updateTextBox()
{
    std::string text = std::string(m_label);

    if (m_hours > 0) {
        text += std::to_string(m_hours) + "h " + std::to_string(m_minutes) + "min " + std::to_string(m_seconds) + "s";
    }
    else if (m_minutes > 0) {
        text += std::to_string(m_minutes) + "min " + std::to_string(m_seconds) + "s";
    }
    else {
        text += std::to_string(m_seconds) + "s";
    }
    
    m_textBox.setTexte(text.c_str());
}

void TimeBox::setPosition(Vector2f position)
{
    m_textBox.setPosition(position);
}

void TimeBox::setTime(int seconds, int minutes, int hours)
{
    m_seconds = seconds;
    m_minutes = minutes;
    m_hours = hours;
    updateTextBox();
}

int TimeBox::getValue() const
{
    return m_seconds;
}

Vector2f TimeBox::getPosition()
{
    return m_textBox.getPosition();
}