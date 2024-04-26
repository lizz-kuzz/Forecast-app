//#include "inc/tools.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_window.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_menu.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_getinfo.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_userinfo.h"
#include <ostream>
#include <string>

//константы параметров окна
const float window_width = 1920;
const float window_height = 1080;

//константы файлов фона и шрифта
const std::string simple_blue_bg    = "res/image/goluboj_tsvet_fon_1920x1080.jpg";
const std::string simple_thick_font = "res/font/BlissproMedium.otf";

//константы для имени пользователя
const size_t MAX_NAME_SIZE = 10;

//доступ к функциям sfml
using namespace sf; 


//--------------------------------------------------------------------------------------------------

int main()
{
    //==================GET NAME===========================

    std::string user_name = window_choose_name();

    std::cout << user_name << std::endl;

    //==================GET CITY===========================

    User_city_t user_city = window_choose_city();

    std::cout << user_city << std::endl;

    //==================SHOW MAIN MENU===========================

    User_info new_user(user_name, user_city);

    window_main();

    return 0;
}