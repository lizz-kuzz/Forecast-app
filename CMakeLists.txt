cmake_minimum_required(VERSION 3.22)
project(weather_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CURL_LIBRARY "-lcurl")
set(PQXX_LIBRARY "-lpqxx")
find_package(CURL REQUIRED)
# find_package(lpqxx REQUIRED)
add_executable(
  weather_app
  src/main.cpp
  server/src/http_request.cpp
  server/src/json_parsing.cpp
  server/src/weather.cpp
  server/src/database.cpp
  front_end/src/app_getinfo.cpp
  front_end/src/app_menu.cpp
  front_end/src/app_window.cpp
  )

target_link_libraries(weather_app curl)
target_link_libraries(weather_app pqxx)
target_link_libraries(weather_app sfml-system)
target_link_libraries(weather_app sfml-window)
target_link_libraries(weather_app sfml-graphics)

target_include_directories(weather_app PUBLIC front_end/include)
target_include_directories(weather_app PUBLIC server/include)
target_include_directories(weather_app PUBLIC external_include)
