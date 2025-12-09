#pragma once

#include <BBOP/Graphics.h>


class SettingsMenu
{
    private :
        Sprite m_background;
        Sprite m_Retour;

    public :
        SettingsMenu();
        ~SettingsMenu();

        void update();
        void Draw();
};