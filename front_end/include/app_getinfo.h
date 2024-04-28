#pragma once

#include "tools.h"
#include "app_window.h"
#include "app_menu.h"
#include "weather.h"
#include <iostream>
#include <string>

//константы параметров окна
// extern const float window_width;
// extern const float window_height;

// //константы файлов фона и шрифта
// extern const std::string simple_blue_bg;
// extern const std::string simple_thick_font;

// //константы для имени пользователя
// extern const size_t MAX_NAME_SIZE;

//--------------------------------------------------------------------------------------------------

size_t      window_choose_mode();
std::string window_choose_name();
User_city_t window_choose_city();
size_t      window_show_city(User_city_t user_city);

int         window_main();
