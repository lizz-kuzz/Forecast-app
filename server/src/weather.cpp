#include "weather.h"
#include "json_parsing.h"

Weather_info::Weather_info(nlohmann::json info, size_t pos) : 
                            temp(info["list"][pos]["main"]["temp"]),
                            temp_feels_like(info["list"][pos]["main"]["feels_like"]),
                            pressure(info["list"][pos]["main"]["pressure"]),
                            wind(info["list"][pos]["wind"]["speed"])
{
    Parsing::parse_data(date, info, pos);
    type = Parsing::parse_weather(info, pos);
    city = DEFAULT;
    // user_name = "atar";
}