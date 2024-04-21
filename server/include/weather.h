#pragma once 
#include <iostream>
#include <nlohmann/json.hpp> 
const size_t JSON_SIZE = 39;

struct Data {
    uint8_t time;
    uint8_t day;
    uint8_t month;
    uint8_t year;
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


class Weather_info {
private:
    double temp;
    double temp_feels_like;
    double pressure;
    double wind;
    Weather_t type;
    Data data;
public:
    Weather_info() = default;
    //constructer from data_base

    //constructer from json 
    Weather_info(nlohmann::json arr_info, size_t pos);
};;
