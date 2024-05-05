#pragma once

#include <iostream>
#include <nlohmann/json.hpp> 
#include <chrono>
#include <thread>
#include <mutex>
		
const size_t WEATHER_ARR_SIZE = 39;

struct Datetime {
    std::string time;
    std::string date;

    // ~Datetime() {};
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
    DEFAULT,
	MOSCOW,			//55.751244 37.618423
	STPETESBURG,	//59.937500 30.308600		
	NOVOSIBIRSK,	//55.050000 82.950000
	YEKATERINBURG,  //56.835600 60.612800		
	DOLOGOPRUDNY,	//55.939831 37.503434	
};

enum User_mode_t {  //LAT       LON
    MODE_AUTHORIZATION,
    MODE_REGISTRATION
};

class User_info {
public: 
    std::string name;
    User_city_t city;
    User_info() = default;
    User_info(std::string name, User_city_t city) : name(name), city(city) {};
};


class Weather_info {
public:
    double temp = 0;
    double temp_feels_like = 0;
    double pressure = 0;
    double wind = 0;
    Weather_t type = None;
    Datetime date;
    User_city_t city = DEFAULT; //TODO: change type
    // std::string user_name;
    Weather_info() = default;
    // Weather_info() : temp(0), temp_feels_like(0), pressure(0), 
                    //  wind(0), type(None) {
                        // date()
                    //  };
    ~Weather_info() {};
    //constructer from data_base

    //constructer from json 
    Weather_info(nlohmann::json arr_info, size_t pos);
};

enum Command_t {
    NONE,
    NAME_EXIST,
    CITY_BY_NAME,
    CHANGE_CITY,
    BREAK_THR2,
    GIVE_INFO,
};

struct Shared_data {
    bool name_exist;
    User_info user;
    std::vector<Weather_info> arr;
};

struct Shared_cmd {
    std::mutex mutex;
    bool give_cmd;
    Command_t cmd;
};
