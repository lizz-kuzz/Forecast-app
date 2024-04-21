#pragma once

#include <nlohmann/json.hpp> 
#include "weather.h"
using json = nlohmann::json;

namespace Parsing
{
void parse_data(Data& data, json& info, size_t pos);
Weather_info* parse(const std::string& buf);
Weather_t parse_weather(json& info, size_t pos);
} // namespace Parsing
