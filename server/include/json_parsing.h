#pragma once

#include <nlohmann/json.hpp> 
#include "weather.h"
using json = nlohmann::json;

class Parsing {
public:
    // Weather_info* arr;
    std::vector<Weather_info> arr;
    Parsing(const std::string& buf);
    ~Parsing();
    static void parse_data(Datetime& date, json& info, size_t pos);
    static Weather_t parse_weather(json& info, size_t pos);
};
