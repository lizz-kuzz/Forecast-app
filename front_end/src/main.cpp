#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/tools.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_window.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_menu.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_getinfo.h"
#include "/home/kate/Рабочий стол/CPP/Forecast-app/front_end/include/app_userinfo.h"
#include <ostream>
#include <string>


//доступ к функциям sfml
using namespace sf; 


//--------------------------------------------------------------------------------------------------

int main()
{
    //==================GET MODE===========================

    size_t user_mode = window_choose_mode();

    std::cout << user_mode << std::endl;
    
    //==================GET NAME===========================

    std::string user_name = window_choose_name();

    std::cout << user_name << std::endl;

    //------wait informatin from serwer about city---------

    //==================GET CITY===========================

    User_city_t user_city = DOLOGOPRUDNY; //defolt

    if (user_mode == MODE_REGISTRATION)
    {
        user_city = window_choose_city();

        std::cout << user_city << std::endl;
    }

    else // user_mode == MODE_AUTHORIZATION
    {
        user_city = DOLOGOPRUDNY; // change, should be get from server

        window_show_city(user_city);

        std::cout << user_city << std::endl;
    }

    //==================SHOW MAIN MENU===========================

    User_info new_user(user_name, user_city);

    window_main();

    return 0;
}