#pragma once

#include <iostream>
#include <nlohmann/json.hpp> 

const size_t WEATHER_ARR_SIZE = 39;

struct Datetime {
    std::string time;
    std::string date;

    ~Datetime() {};
    // Datetime operator=(const Datetime lr) {
    //     Datetime tmp{lr.date, lr.time};
    //     return tmp;
    // }; 
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


enum User_city_t {  //LAT       LON
	MOSCOW,			//55.755800 37.617200
	STPETESBURG,	//59.937500 30.308600		
	NOVOSIBIRSK,	//55.050000 82.950000
	YEKATERINBURG,  //56.835600 60.612800		
	DOLOGOPRUDNY,	//37.503434	55.939831
    DEFAULT
};

enum User_mode_t {  //LAT       LON
    MODE_AUTHORIZATION,
    MODE_REGISTRATION
};

class User_info {
public: 
    std::string user_name;
    User_city_t city;
    User_info(std::string user_name, User_city_t city) : user_name(user_name), city(city) {};
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
