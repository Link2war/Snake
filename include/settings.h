#pragma once

#include <BBOP/Graphics.h>


class Settings
{
    private :
        Sprite * background;

    public :
        Settings();

        void update();
        void Draw();
};