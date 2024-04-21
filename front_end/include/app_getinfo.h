#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/tools.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_window.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_menu.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_userinfo.h"
#include <ostream>
#include <string>

//константы параметров окна
extern const float window_width;
extern const float window_height;

//константы файлов фона и шрифта
extern const std::string simple_blue_bg;
extern const std::string simple_thick_font;

//константы для имени пользователя
extern const size_t MAX_NAME_SIZE;

//--------------------------------------------------------------------------------------------------
std::string window_choose_name();
int         window_main();
User_city_t window_choose_city();
