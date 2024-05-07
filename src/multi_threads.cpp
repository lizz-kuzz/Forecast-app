#include "multi_threads.h"

#include "app_getinfo.h"
#include "database.h"

//====================SHARED_DATA================================

Shared_data shdata;
Shared_cmd thread;

//==============================================================

void client_thread_funk(void) {
    User_mode_t user_mode;
    std::cout << "Thread 1 executing\n";

    //==================GET MODE===========================

    thread.mutex.lock();
    thread.give_cmd = false;
    user_mode = window_choose_mode();

    std::cout << "user mode:" << user_mode << std::endl;

    if (user_mode == MODE_REGISTRATION) {
        //==================GET NAME===========================
        while (true) {
            shdata.user.name = window_choose_name();
            shdata.user.name.pop_back();
            std::cout << "user name:" << shdata.user.name << std::endl;
            thread.cmd = NAME_EXIST;
            thread.give_cmd = true;
            thread.mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            thread.mutex.lock();

            if (shdata.name_exist == false) break;

            // TODO: ADD FUNC with window this name already exist
            window_name_error("This name already exist");
        }

        //==================GET CITY===========================

        shdata.user.city = window_choose_city();

    } else if (user_mode == MODE_AUTHORIZATION) {
        //==================GET NAME===========================

        while (true) {  // checking exist this name in db or not
            shdata.user.name = window_choose_name();
            shdata.user.name.pop_back();
            std::cout << "user name:" << shdata.user.name << std::endl;
            thread.cmd = NAME_EXIST;
            thread.give_cmd = true;
            thread.mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            thread.mutex.lock();

            if (shdata.name_exist == true) break;

            // TODO: ADD FUNC with window that this name dont exist
            window_name_error("This name doesn't exist");
        }
        //==================GET CITY===========================

        thread.cmd = CITY_BY_NAME;
        thread.give_cmd = true;
        thread.mutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        thread.mutex.lock();

        bool change_sity = window_show_city(shdata.user.city);

        if (change_sity) {
            shdata.user.city = window_choose_city();
            thread.cmd = CHANGE_CITY;
            thread.give_cmd = true;
            thread.mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            thread.mutex.lock();
        }
    }

    thread.cmd = GIVE_INFO;
    thread.give_cmd = true;
    thread.mutex.unlock();

    //==================SHOW MAIN MENU===========================

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    thread.mutex.lock();
    window_main(shdata.arr);

    std::cout << "thread 1 end" << std::endl;
    thread.cmd = BREAK_THR2;
    thread.give_cmd = true;
    thread.mutex.unlock();
}

void server_thread_funk(void) {
    std::cout << "Thread 2 executing\n";
    Database db;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    while (true) {
        thread.mutex.lock();
        std::cout << "thread 2 catch mutex" << std::endl;

        if (thread.give_cmd) {
            std::cout << "thread.cmd = " << thread.cmd << std::endl;
            if (thread.cmd == NAME_EXIST) {
                shdata.name_exist = db.is_name_exist(shdata.user);
                std::cout << std::endl
                        << "client " << shdata.user.name
                        << " exist: " << shdata.name_exist << std::endl;
            } else if (thread.cmd == CITY_BY_NAME) {
                shdata.user.city = db.give_city_by_name(shdata.user);
                std::cout << std::endl
                        << "client " << shdata.user.name
                        << " city: " << shdata.user.city << std::endl;
            } else if (thread.cmd == CHANGE_CITY) {
                db.change_city(shdata.user);
            } else if (thread.cmd == BREAK_THR2) {
                break;
            } else if (thread.cmd == GIVE_INFO) {
                db.give_avg_info_user(shdata.user, shdata.arr);
            }
            thread.cmd = NONE;
        }
        thread.give_cmd = false;
        thread.mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "Thread 2 end" << std::endl;
}
