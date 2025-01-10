#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>

class Menu
{
    private :
        Sprite * background;
        Sprite * start_buton;
        Sprite * settings_buton;

        bool on_start;
        bool on_settings;
        bool start;
        

    public :
        Menu();

        void Draw(Scene scene);
        void checkStart(GLFWwindow * window);
        bool Settings();
        bool pressStart();

        void onStart(GLFWwindow * window);
        void onSettings(GLFWwindow * window);

        void reset();
};