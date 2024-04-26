cmake_minimum_required(VERSION 3.22)
project(weather_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CURL_LIBRARY "-lcurl")
set(PQXX_LIBRARY "-lpqxx")
find_package(CURL REQUIRED)
# find_package(lpqxx REQUIRED)
add_executable(
  weather_server
  src/main.cpp
  src/http_request.cpp
  src/json_parsing.cpp
  src/weather.cpp
  src/database.cpp
  )

target_link_libraries(weather_server curl)
target_link_libraries(weather_server pqxx)

target_include_directories(weather_server PUBLIC include)
target_include_directories(weather_server PUBLIC ../external_include)
