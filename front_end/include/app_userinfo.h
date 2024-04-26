#pragma once
#include "tools.h"

enum User_city_t {  //LAT       LON
	MOSCOW,			//55.755800 37.617200
	STPETESBURG,	//59.937500 30.308600		
	NOVOSIBIRSK,	//55.050000 82.950000
	YEKATERINBURG,  //56.835600 60.612800		
	DOLOGOPRUDNY,	//37.503434	55.939831
    ERROR
};

class User_info
{
private:
    std::string user_name_;
    User_city_t user_city_ = DOLOGOPRUDNY;

public:
    User_info(std::string user_name, User_city_t user_city)
        :user_name_(user_name), user_city_(user_city)
    {

    }
};
