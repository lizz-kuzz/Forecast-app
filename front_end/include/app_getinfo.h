#pragma once

#include <iostream>
#include <string>

#include "app_menu.h"
#include "app_window.h"
#include "tools.h"
#include "weather.h"

//--------------------------------------------------------------------------------------------------

User_mode_t window_choose_mode();
std::string window_choose_name();
User_city_t window_choose_city();
size_t window_show_city(User_city_t user_city);

int window_name_error(const std::string error_text);

int window_main(const std::vector<Weather_info>& arr);
