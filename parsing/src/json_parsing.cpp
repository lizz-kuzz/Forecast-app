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
    std::string str_buf = info["list"][pos]["weather"][0]["main"];
    if (str_buf == "clear_sky") {
        return Clear_sky;
    } else if (str_buf == "clouds") {
        return Clouds;
    }
    return None;//add more variants

}
