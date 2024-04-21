cmake_minimum_required(VERSION 3.22)
project(weather_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


add_executable(
  weather_server
  src/main.cpp
  src/http_request.cpp
  src/json_parsing.cpp
  src/weather.cpp
  )
  
target_link_libraries(weather_server curl)
target_include_directories(weather_server PUBLIC include)
