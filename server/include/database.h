#pragma once 

#include <pqxx/pqxx>
#include <optional>
#include "weather.h"
#include "http_request.h"
#include "json_parsing.h"

// using namespace pqxx; remember!!

struct City_coord {
    double lat;
    double lon;
};

class Database {
private:
    pqxx::connection weather_database{"postgresql://lizzkuzz:1511@localhost/weatherdb"};
    pqxx::work request{weather_database};

public:
    Database() = default;
    ~Database();

    // Weather_info request_by_name(User_info client);
    void add_info_user(const User_info& client);
    void update_info_user(const User_info& client);
    void give_all_info_user(const User_info& client, std::vector<Weather_info>& arr);
    void give_avg_info_user(const User_info& client, std::vector<Weather_info>& arr);
    bool is_info_exist(const User_info& client);
    bool is_name_exist(const User_info& client);
    void give_city_coord(City_coord& city, const User_info& client);
    User_city_t give_city_by_name(const User_info& client);

// добавить проверку на то есть клиент или нет если есть то обновить инфу а если нет то отправить на клиента что такого пользователя нет 
};