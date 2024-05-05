#include "multi_threads.h"
#include "database.h"
#include "app_getinfo.h"

//====================SHARED_DATA================================

User_info user;
std::vector<Weather_info> arr;
Shared_data shdata;
//=====================MULTI THREAD MUTEX=======================
Shared_cmd thread;

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
    User_mode_t user_mode; 
    std::cout << "Thread 1 executing\n";

    //==================GET MODE===========================

    thread.mutex.lock();
    thread.give_cmd = false;
    user_mode = window_choose_mode();

    std::cout << "user mode:" << user_mode << std::endl;
    
    //==================GET NAME===========================

    //user_name = window_choose_name();

    //std::cout << "user name:" << user_name << std::endl;

    //------wait informatin from serwer about city---------
    //user_check_by_name(); ///////ADD////////

    //==================GET CITY===========================

    if (user_mode == MODE_REGISTRATION) {
        while (true) { //checking exist this name in db or not 
            user.name = window_choose_name();
            user.name.pop_back();
            std::cout << "user name:" << user.name << std::endl;
            thread.cmd = NAME_EXIST;
            thread.give_cmd = true;
            thread.mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            thread.mutex.lock();

            if (shdata.name_exist == false) break; 
            
            // TODO: ADD FUNC with window this name already exist 
        }


        user.city = window_choose_city();
        // TODO: thihk about it thread.mutex.unlock();

    } else if (user_mode == MODE_AUTHORIZATION) {

        while (true) { //checking exist this name in db or not 
            user.name = window_choose_name();
            user.name.pop_back();
            std::cout << "user name:" << user.name << std::endl;
            thread.cmd = NAME_EXIST;
            thread.give_cmd = true;
            thread.mutex.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            thread.mutex.lock();

            if (shdata.name_exist == true) break; 
            
            // TODO: ADD FUNC with window that this name dont exist 
        }

        thread.cmd = CITY_BY_NAME;
        thread.give_cmd = true;
        thread.mutex.unlock();

        //     user.city = DOLOGOPRUDNY; // change, should be get from server ---> in auth_get_info()
        //     thr_mutex.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        thread.mutex.lock();
        window_show_city(user.city);


        //TODO: ADD CHANGE SITY WINDOW

        }
        
        
    //     auth_get_info();//--> *city
    //                     //--> *weather



    // std::cout << "user city:" << user.city << std::endl;

    // //==================SHOW MAIN MENU===========================

    // User_info new_user(user.name, user.city); //add weather

    // thr_mutex.lock();
    // Database db;
    // User_info my {"real", MOSCOW};

    // db.give_avg_info_user(my, arr);

    
    // window_main(arr);
    // thr_mutex.unlock();
    std::cout << "thread 1 end" << std::endl;


}

void server_thread_funk(void)
{

    std::cout << "Thread 2 executing\n";
    // User_info my {"real", MOSCOW};
    Database db;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    while (true) {
        thread.mutex.lock();
        std::cout << "thread 2 catch mutex" << std::endl;
        if (thread.give_cmd) {
            if (thread.cmd == NAME_EXIST) {
                shdata.name_exist = db.is_name_exist(user);
                std::cout << user.name << std::endl;
                std::cout << std::endl << "client " << user.name << " exist: " << shdata.name_exist << std::endl;
                thread.cmd = NONE;
            } else if (thread.cmd == CITY_BY_NAME) {
                user.city = db.give_city_by_name(user);
                std::cout << std::endl << "client " << user.name << " city: " << user.city << std::endl;
            }
        } 
        thread.give_cmd = false;
        thread.mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        

    }


    // // db.add_info_user(my);
    // db.update_info_user(my);
    // // db.is_info_exist(my);
    // std::vector<Weather_info> arr;
    // db.give_avg_info_user(my, arr);

    // for (auto elem : arr) {
    //     std::cout << elem.date.date << " " << elem.pressure << " " << std::endl;
    // }
    // User_info my {"real", MOSCOW};
    // Database db;
    // // db.add_info_user(my);
    // db.update_info_user(my);
    // // db.is_info_exist(my);
    // std::vector<Weather_info> arr;
    // // db.give_info_user(my, arr);
    // std::cout << "OK" << std::endl;


  

}
