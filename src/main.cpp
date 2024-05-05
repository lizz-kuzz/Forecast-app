#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include "database.h"

#include "app_getinfo.h"

#include "multi_threads.h"
#include <thread>



int main() {

    // Database db;
    // User_info info{"real", DOLOGOPRUDNY};
    // std::cout << db.is_name_exist(info);
    std::thread client_thr(client_thread_funk);
    std::thread server_thr(server_thread_funk);

    client_thr.join();
    server_thr.join();


}
