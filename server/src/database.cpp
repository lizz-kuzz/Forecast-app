#include "database.h" 

Database::~Database() {
    request.commit();
    weather_database.disconnect();

}

void Database::add_info_user(const User_info& client) {
    HTTP::Request weather;
    City_coord coord;
    give_city_coord(coord, client);
    weather.get_buffer_from_api(coord.lat, coord.lon); //TODO: add here coord diffrent countries + bd

    Parsing city_weather(weather.buffer);

    for (size_t i = 0; i < WEATHER_ARR_SIZE; ++i) {
        std::string sql_request{"insert into weather(user_name, city, data_," 
                                "time_, temp, temp_feels_like, pressure, "
                                "wind, type_) " 
                                "values" 
                            "('" + client.name + "', " + std::to_string(client.city) + 
                            ", '" + city_weather.arr[i].date.date + "', '" + city_weather.arr[i].date.time + 
                            "', " + std::to_string(city_weather.arr[i].temp) + ", " + std::to_string(city_weather.arr[i].temp_feels_like) + 
                            ", " +std::to_string(city_weather.arr[i].pressure) + ", " + std::to_string(city_weather.arr[i].wind) + ", " 
                            + std::to_string(city_weather.arr[i].type) + ");"};
        pqxx::result res_request{request.exec(sql_request.c_str())};   
        
    }

}


void Database::update_info_user(const User_info& client) {
    std::string sql_request{"delete from weather "
                            "where user_name = '" + client.name + "' and " 
                            "city = " + std::to_string(client.city) + ";"};
    pqxx::result res_request{request.exec(sql_request.c_str())};   
    add_info_user(client);
}

void Database::give_all_info_user(const User_info& client, std::vector<Weather_info>& arr) {
     
    std::string sql_request{"select * from weather "
                            "where user_name = '" + client.name + "' and " 
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

void Database::give_avg_info_user(const User_info& client, std::vector<Weather_info>& arr) {
    update_info_user(client);
    std::string sql_request{"select  weather.city, "
                                    "weather.user_name,"
                                    "weather.data_," 
                                    "avg(temp),"
                                    "avg(temp_feels_like),"
                                    "avg(pressure),"
                                    "avg(wind), "
                                    "avg(type_)"
                                    "from weather where weather.city = " + std::to_string(client.city) + 
                                    "and weather.user_name = '" + client.name + 
                                    "' group by weather.data_, "
                                    "weather.city, weather.user_name " 
                                    "order by weather.data_;" };

    pqxx::result res_request{request.exec(sql_request.c_str())};   
    
    for (auto row : res_request) {
        Weather_info elem;
        elem.city = client.city;
        elem.date.date = row[2].as<std::string>();
        elem.temp = row[3].as<float>();
        elem.temp_feels_like = row[4].as<float>();
        elem.pressure = row[5].as<float>();
        elem.wind = row[6].as<float>();
        float type_elem = row[7].as<float>();
        if (type_elem >= (static_cast<int>(type_elem) + 0.5)) {
            elem.type = static_cast<Weather_t>(static_cast<int>(type_elem) + 1);
        } else {
            elem.type = static_cast<Weather_t>(static_cast<int>(type_elem));
        }

        arr.push_back(elem);
    }

}



bool Database::is_info_exist(const User_info& client) {
    std::string sql_request{"select * from weather "
                            "where user_name = '" + client.name + "' and " 
                            "city = " + std::to_string(client.city) + ";"};
    pqxx::result res_request{request.exec(sql_request.c_str())};   

    return res_request.empty();
}

bool Database::is_name_exist(const User_info& client) {

    std::string sql_request{"select * from weather "
                            "where weather.user_name = '" + client.name + "';"};
                            // std::cout << sql_request << std::endl;
    pqxx::result res_request{request.exec(sql_request.c_str())};   

    return !res_request.empty();
}


User_city_t Database::give_city_by_name(const User_info& client) {
    std::string sql_request{"select city from weather "
                            "where user_name = '" + client.name + "';"};
    pqxx::result res_request{request.exec(sql_request.c_str())};  

    return static_cast<User_city_t>(res_request.front()[0].as<int>());
}

void Database::give_city_coord(City_coord& city, const User_info& client) {
    std::string sql_request{"select * from city_coord "
                            "where city = " + std::to_string(client.city) + ";"};

    pqxx::result res_request{request.exec(sql_request.c_str())};   
    city.lat = res_request.front()[0].as<float>();
    city.lat = res_request.front()[1].as<float>();



}