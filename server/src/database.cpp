#include "database.h" 

Database::~Database() {
    request.commit();
    weather_database.disconnect();

}

// Weather_info Database::request_by_name(User_info client) {

// }

void Database::add_info_user(const User_info& client) {
    HTTP::Request weather;
    weather.get_buffer_from_api(); //TODO: add here coord diffrent countries + bd

    Parsing city_weather(weather.buffer);

    for (size_t i = 0; i < WEATHER_ARR_SIZE; ++i) {
        std::string sql_request{"insert into weather(user_name, city, data_," 
                                "time_, temp, temp_feels_like, pressure, "
                                "wind, type_) " 
                                "values" 
                            "('" + client.user_name + "', " + std::to_string(client.city) + 
                            ", '" + city_weather.arr[i].date.date + "', '" + city_weather.arr[i].date.time + 
                            "', " + std::to_string(city_weather.arr[i].temp) + ", " + std::to_string(city_weather.arr[i].temp_feels_like) + 
                            ", " +std::to_string(city_weather.arr[i].pressure) + ", " + std::to_string(city_weather.arr[i].wind) + ", '" + std::to_string(city_weather.arr[i].type) + "');"};
        pqxx::result res_request{request.exec(sql_request.c_str())};   
        
    }

}


void Database::update_info_user(const User_info& client) {
    std::string sql_request{"delete from weather "
                            "where user_name = '" + client.user_name + "' and " 
                            "city = " + std::to_string(client.city) + ";"};
    pqxx::result res_request{request.exec(sql_request.c_str())};   
    add_info_user(client);
}

void Database::give_info_user(const User_info& client, std::vector<Weather_info> arr) {
     
    std::string sql_request{"select * from weather "
                            "where user_name = '" + client.user_name + "' and " 
                            "city = " + std::to_string(client.city) + ";"};

    pqxx::result res_request{request.exec(sql_request.c_str())};   
    
    for (size_t i = 0; auto row : res_request) {
        Weather_info elem;
        elem.city = static_cast<User_city_t>(row[1].as<int>());
        elem.date.date = row[2].as<std::string>();
        elem.date.time = row[3].as<std::string>();
        elem.temp = row[4].as<float>();
        elem.temp_feels_like = row[5].as<float>();
        elem.pressure = row[6].as<float>();
        elem.wind = row[7].as<float>();
        elem.type = static_cast<Weather_t>(row[8].as<int>());
        ++i;
        arr.push_back(elem);
    }

}


bool Database::is_info_exist(const User_info& client) {
    std::string sql_request{"select * from weather "
                            "where user_name = '" + client.user_name + "' and " 
                            "city = " + std::to_string(client.city) + ";"};
    pqxx::result res_request{request.exec(sql_request.c_str())};   

    return res_request.empty();
}
