#include "threads.h"
#include <iostream>

#include <curl/curl.h>
#include "database.h"

#include "app_getinfo.h"


const size_t MODE_REGISTRATION = 1;


void client_thread_funk(void)
{
    std::cout << "Thread 1 executing\n";

    //==================GET MODE===========================

    size_t user_mode = window_choose_mode();

    std::cout << user_mode << std::endl;
    
    //==================GET NAME===========================

    std::string user_name = window_choose_name();

    std::cout << user_name << std::endl;

    //------wait informatin from serwer about city---------

    //==================GET CITY===========================

    User_city_t user_city = DOLOGOPRUDNY; //defolt

    if (user_mode == MODE_REGISTRATION)
    {
        user_city = window_choose_city();

        std::cout << user_city << std::endl;
    }

    else // user_mode == MODE_AUTHORIZATION
    {
        user_city = DOLOGOPRUDNY; // change, should be get from server

        window_show_city(user_city);

        std::cout << user_city << std::endl;
    }

    //==================SHOW MAIN MENU===========================

    User_info new_user(user_name, user_city);

    window_main();

}

void server_thread_funk(void)
{
    std::cout << "Thread 2 executing\n";

    User_info my {"real", MOSCOW};
    Database db;
    db.add_info_user(my);
    // db.update_info_user(my);
    // db.is_info_exist(my);
    // Weather_info* arr = new Weather_info[WEATHER_ARR_SIZE];
    // db.give_info_user(my, arr);
    // std::cout << "OK" << std::endl;


    // for (size_t i = 0; i < WEATHER_ARR_SIZE; ++i) {
    //     std::string sql_request{"values" 
    //                         "('" + my.user_name + "', " + std::to_string(my.city) + 
    //                         ", '" + arr[i].date.date + "', '" + arr[i].date.time + 
    //                         "', " + std::to_string(arr[i].temp) + ", " + std::to_string(arr[i].temp_feels_like) + 
    //                         ", " +std::to_string(arr[i].pressure) + ", " + std::to_string(arr[i].wind) + ", '" + std::to_string(arr[i].type) + "');"};
    //     std::cout << sql_request << std::endl;
    // }

    // delete[] arr;

    // std::string readBuffer;

    // HTTP::Request weather;

    
    // weather.get_buffer_from_api(); //add here coord diffrent countries + bd

    // Parsing city_weather(weather.buffer);

    // pqxx::connection weather_database{"postgresql://lizzkuzz:1511@localhost/weatherdb"};
    // pqxx::work request{weather_database};


    // int city = 1;
    // std::string sql_request1{"insert into weather(user_name, city, data_," 
    //                         "time_, temp, temp_feels_like, pressure, "
    //                         "wind, type_) " 
    //                         "values" 
    //                       "('marina', 2, '2024-04-26', '3:00:00', 10.2, 19.4, 444, 5.3, 'sunny');"};
    // pqxx::result res_request1{request.exec(sql_request1.c_str())};
    // std::string sql_request2{"select city, temp from weather where user_name = 'marina'"};
    // pqxx::result res_request2{request.exec(sql_request2.c_str())};
    // std::cout << res_request2.empty() << std::endl;
    // for (auto row : res_request2) {
    //     std::cout 
    //     << row[0] << " " << row[1]
    //     << std::endl;
    // }

    // request.commit();
}