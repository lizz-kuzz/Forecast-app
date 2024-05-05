#pragma once

#include <optional>
#include <pqxx/pqxx>

#include "http_request.h"
#include "json_parsing.h"
#include "weather.h"


struct City_coord {
    double lat;
    double lon;
};

class Database {
private:
    pqxx::connection weather_database{
        "postgresql://lizzkuzz:1511@localhost/weatherdb"};
    pqxx::work request{weather_database};

public:
    Database() = default;
    ~Database();

    void add_info_user(const User_info& client);
    void update_info_user(const User_info& client);
    void give_all_info_user(const User_info& client,
                            std::vector<Weather_info>& arr);
    void give_avg_info_user(const User_info& client,
                            std::vector<Weather_info>& arr);
    bool is_info_exist(const User_info& client);
    bool is_name_exist(const User_info& client);
    void give_city_coord(City_coord& city, const User_info& client);
    User_city_t give_city_by_name(const User_info& client);

};