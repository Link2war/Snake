#pragma once

#include <BBOP/Graphics.h>


class Settings
{
    private :
        Sprite * background;
        Sprite * Retour;

    public :
        Settings();

        void update();
        void Draw();
};