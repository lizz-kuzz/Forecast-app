#pragma once 

#include <pqxx/pqxx>
#include <optional>
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
    void add_info_user(const User_info& client);
    void update_info_user(const User_info& client);
    void give_info_user(const User_info& client, Weather_info *arr);


// добавить проверку на то есть клиент или нет если есть то обновить инфу а если нет то отправить на клиента что такого пользователя нет 
};