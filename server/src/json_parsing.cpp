#include "../include/json_parsing.h"

void Parsing::parse(const std::string& buf) {
    json info;

    info = json::parse(buf);
    Weather_info* weather_arr = new Weather_info[JSON_SIZE];
    for (size_t i = 0; i < JSON_SIZE; ++i) {
       weather_arr[i] = Weather_info(info, i);
    }
}

void Parsing::parse_data(Data& data, json& info, size_t pos) {
        
    std::string str_buf = info["list"][pos]["dt_txt"];
    std::cout << str_buf << std::endl;
    std::string res_buff;
    std::copy(str_buf.begin(), str_buf.begin() + 4, std::back_inserter(res_buff));
    data.year = std::atoi(res_buff.c_str());
    res_buff.clear();
    std::copy(str_buf.begin() + 5, str_buf.begin() + 7, std::back_inserter(res_buff));
    data.month = std::atoi(res_buff.c_str());
    res_buff.clear();
    std::copy(str_buf.begin() + 8, str_buf.begin() + 10, std::back_inserter(res_buff));
    data.day = std::atoi(res_buff.c_str());
    res_buff.clear(); 
    std::copy(str_buf.begin() + 11, str_buf.begin() + 13, std::back_inserter(res_buff));
    data.time = std::atoi(res_buff.c_str());
    res_buff.clear();
}

Weather_t Parsing::parse_weather(json& info, size_t pos) {
    std::string str_buf = info["list"][pos]["weather"][0]["description"];
    if (str_buf == "clear sky") {
        return Clear_sky;
    } else if (str_buf == "few clouds") {
        return Few_clouds;
    } else if (str_buf == "few clouds") {
        return Few_clouds;
    } else if (str_buf == "scattered clouds") {
        return Scattered_clouds;
    } else if (str_buf == "overcast clouds") {
        return Overcast_clouds;
    } else if (str_buf == "light rain") {
        return Light_rain;
    } else if (str_buf == "moderate rain") {
        return Moderate_rain;
    } else if (str_buf == "broken clouds") {
        return Broken_clouds;
    }
    return None;//add more variants

}
