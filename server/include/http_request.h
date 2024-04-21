
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp> 

const double DOLGOPA_LAT = 37.503434;
const double DOLGOPA_LON = 55.939831;

namespace HTTP {
struct Request {
    std::string buffer;
    Request() = default;
    void get_buffer_from_api(double lat = DOLGOPA_LAT, double lon = DOLGOPA_LON);
};
} //namespace HTTP