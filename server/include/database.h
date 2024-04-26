#pragma once 

#include <pqxx/pqxx>
#include "weather.h"
#include "http_request.h"
#include "json_parsing.h"

// using namespace pqxx; remember!!

class Database {
private:
    pqxx::connection weather_database{"postgresql://lizzkuzz:1511@localhost/weatherdb"};
    pqxx::work request{weather_database};

public:
    Database() = default;
    ~Database();

    // Weather_info request_by_name(User_info client);
    Weather_info add_info_about_city(const User_info& client);

};