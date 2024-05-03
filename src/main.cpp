#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include "database.h"

#include "app_getinfo.h"

#include "multi_threads.h"
#include <thread>



int main() {

    std::cout << "Thread 2 executing\n";

    User_info my {"real", MOSCOW};
    Database db;
    // db.add_info_user(my);
    db.update_info_user(my);
    // db.is_info_exist(my);
    std::vector<Weather_info> arr;
    db.give_avg_info_user(my, arr);

    for (auto elem : arr) {
        std::cout << elem.date.date << " " << elem.pressure << " " << std::endl;
    }
    std::cout << "OK" << std::endl;
    // std::thread client_thr(client_thread_funk);
    // std::thread server_thr(server_thread_funk);

    // client_thr.join();
    // server_thr.join();


}
