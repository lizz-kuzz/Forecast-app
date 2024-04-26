#pragma once

#include <iostream>
#include <nlohmann/json.hpp> 
const size_t WEATHER_ARR_SIZE = 39;

struct Datetime {
    std::string time;
    std::string date;

    ~Datetime() {};
};

enum Weather_t {
    Clear_sky,
    Few_clouds, 
    Scattered_clouds, 
    Overcast_clouds,
    Light_rain, 
    Moderate_rain, 
    Broken_clouds,
    None,
};

class User_info {
public: 
    std::string user_name;
    int city;
};


class Weather_info {
public:
    double temp;
    double temp_feels_like;
    double pressure;
    double wind;
    Weather_t type;
    Datetime date;
    // std::string user_name;
    int city; //TODO: change type
    Weather_info() = default;
    ~Weather_info() {};
    //constructer from data_base

    //constructer from json 
    Weather_info(nlohmann::json arr_info, size_t pos);
};;
