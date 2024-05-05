#include "json_parsing.h"

Parsing::Parsing(const std::string& buf) {
  json info;

  info = json::parse(buf);
  for (size_t i = 0; i < WEATHER_ARR_SIZE; ++i) {
    arr.push_back(Weather_info(info, i));
  }
}

void Parsing::parse_data(Datetime& date, json& info, size_t pos) {
  std::string str_buf = info["list"][pos]["dt_txt"];

  std::copy(str_buf.begin(), str_buf.begin() + 10,
            std::back_inserter(date.date));

  std::copy(str_buf.begin() + 11, str_buf.end(), std::back_inserter(date.time));
}

Weather_t Parsing::parse_weather(json& info, size_t pos) {
  std::string str_buf = info["list"][pos]["weather"][0]["description"];

  if (str_buf == "clear sky") {
    return Clear_sky;
  } else if (str_buf == "few clouds" || str_buf == "scattered clouds" ||
             str_buf == "overcast clouds" || str_buf == "broken clouds") {
    return Clouds;
  } else if (str_buf == "light rain" || str_buf == "moderate rain") {
    return Rain;
  }
  return None;  // add more variants
}

Parsing::~Parsing() {
  // delete[] arr;
}