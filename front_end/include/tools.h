#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//------------------------------------------------------------------------------------------------------

#include <vector>
#include <iostream>

//------------------------------------------------------------------------------------------------------

//константы параметров окна
const float window_width = 1920;
const float window_height = 1080;

//константы файлов фона и шрифта
const std::string simple_blue_bg    = "res/image/goluboj_tsvet_fon_1920x1080.jpg";
const std::string simple_thick_font = "res/font/BlissproMedium.otf";

//константы для пользователя
const size_t MAX_NAME_SIZE        = 10;
const size_t MODE_AUTHORIZATION   = 0;
const size_t MODE_REGISTRATION    = 1;
const size_t NEED_CHANGE_CITY     = 0;
const size_t NO_NEED_CHANGE_CITY  = 1;