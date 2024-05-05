#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>

const size_t WEATHER_ARR_SIZE = 39;

enum Weather_t {
    Clear_sky,
    Clouds,
    Rain,
    None,
};

enum User_city_t {  // LAT       LON
    DEFAULT,
    MOSCOW,         // 55.751244 37.618423
    STPETESBURG,    // 59.937500 30.308600
    NOVOSIBIRSK,    // 55.050000 82.950000
    YEKATERINBURG,  // 56.835600 60.612800
    DOLOGOPRUDNY,   // 55.939831 37.503434
};

enum User_mode_t {  // LAT       LON
    MODE_AUTHORIZATION,
    MODE_REGISTRATION
};

enum Command_t {
  NONE,
  NAME_EXIST,
  CITY_BY_NAME,
  CHANGE_CITY,
  BREAK_THR2,
  GIVE_INFO,
};

struct Datetime {
    std::string time;
    std::string date;
};

class User_info {
public:
    std::string name;
    User_city_t city;
    User_info() = default;
    User_info(std::string name, User_city_t city) : name(name), city(city){};
};

class Weather_info {
public:
    double temp = 0;
    double temp_feels_like = 0;
    double pressure = 0;
    double wind = 0;
    Weather_t type = None;
    Datetime date;
    User_city_t city = DEFAULT;
    Weather_info() = default;
    ~Weather_info(){};

    // constructer from json
    Weather_info(nlohmann::json arr_info, size_t pos);
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
