#pragma once

#include <BBOP/Graphics.h>


class SettingsMenu
{
    private :
        Sprite background;
        Sprite Retour;

    public :
        SettingsMenu();
        ~SettingsMenu();

        void update();
        void Draw();
};