#include "multi_threads.h"
#include <iostream>

#include <curl/curl.h>
#include "database.h"

#include "app_getinfo.h"

//====================CONSTANTS================================

User_mode_t user_mode; 
User_info user;
std::vector<Weather_info> arr;

//=====================MULTI THREAD MUTEX=======================

std::mutex  thr_mutex;

//=====================REQUESTS TO SERVER=======================
//-->1 name alreday exist; 
//-->0 opposit;

//-->1 name not exist; 
//-->0 opposit;
bool auth_user_check_by_name(){return 0;};

void regs_get_info(){};
void auth_get_info(){};

bool regs_user_check_by_name() {

    return 0;
    
};

//==============================================================


void client_thread_funk(void)
{
    std::cout << "Thread 1 executing\n";

    //==================GET MODE===========================

    thr_mutex.lock();
    user_mode = window_choose_mode();
    thr_mutex.unlock();

    std::cout << "user mode:" << user_mode << std::endl;
    
    //==================GET NAME===========================

    //user_name = window_choose_name();

    //std::cout << "user name:" << user_name << std::endl;

    //------wait informatin from serwer about city---------
    //user_check_by_name(); ///////ADD////////

    //==================GET CITY===========================

    if (user_mode == MODE_REGISTRATION)
    {
        thr_mutex.lock();
        user.name = window_choose_name();
        thr_mutex.unlock();

        std::cout << "user name:" << user.name << std::endl;

        while(regs_user_check_by_name()) ///////ADD//////// --->server-->yes/no
        {
            //-->1 name alreday exist;
            thr_mutex.lock(); 
            user.name = window_choose_name();
            thr_mutex.unlock();
        }

        thr_mutex.lock();
        user.city = window_choose_city();
        thr_mutex.unlock();

        regs_get_info(); //--> *weather
    }

    else // user_mode == MODE_AUTHORIZATION
    {
        thr_mutex.lock();
        user.name = window_choose_name();
        thr_mutex.unlock();

        std::cout << "user name:" << user.name << std::endl;

        while(auth_user_check_by_name()) ///////ADD//////// --->server-->yes/no
        {
        //-->1 name not exist; 
        thr_mutex.lock();
        user.name = window_choose_name();
        thr_mutex.unlock();
        }
        
        
        auth_get_info();//--> *city
                        //--> *weather

        user.city = DOLOGOPRUDNY; // change, should be get from server ---> in auth_get_info()
        thr_mutex.lock();
        window_show_city(user.city);
        thr_mutex.unlock();
    }


    std::cout << "user city:" << user.city << std::endl;

    //==================SHOW MAIN MENU===========================

    User_info new_user(user.name, user.city); //add weather

    thr_mutex.lock();
    window_main();
    thr_mutex.unlock();

}

void server_thread_funk(void)
{


    std::cout << "Thread 2 executing\n";

    User_info my {"real", MOSCOW};
    Database db;
    // db.add_info_user(my);
    db.update_info_user(my);
    // db.is_info_exist(my);
    std::vector<Weather_info> arr;
    // db.give_info_user(my, arr);
    std::cout << "OK" << std::endl;


  

}
