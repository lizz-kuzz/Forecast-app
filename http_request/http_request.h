
#include <iostream>
#include <curl/curl.h>
#include <fstream>

const double DOLGOPA_LAT = 37.503434;
const double DOLGOPA_LON = 55.939831;


namespace HTTP {
class Parsing {
private: 
    std::string buffer;
public:
    Parsing() = default;
    void get_buffer(double lat = DOLGOPA_LAT, double lon = DOLGOPA_LON);
};
} //namespace HTTP