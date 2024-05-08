####  🏙️ Forecast-App

### 🌍 Be aware of the weather

With Forecast-App, you can explore the weather in your city and beyond. We offer an array of features to keep you informed and prepared:

- 🌟 **View Current Weather:** Stay up-to-date with real-time weather conditions in your area.
- 🌅 **View Weather on today or tomorrow:** Plan your day effectively with our forecasts.
- 📆 **View the Weather for the 3 or 5 days:** Get a week-long weather outlook easy.
- 🌡️ **View Detailed Weather Data:**  You can see temperature, pressure and wind speed.
- 🌆 **Choose Your City:** Choose your location city from your list.


### 🌐 Reliable Data Sources

We fetch weather data from [openweathermap](http://openweathermap.org/).

### 🎨 Visual interface

Our application has a window interface. 
For its implementation, we used the graphic library: *SFML*.

We choose [SFML](https://www.sfml-dev.org/) becouse it provides a simple interface to ease the development.

10 windows open in our application:

In the 1 window `User_mode_t window_choose_mode()` client selects the mode of authorization or registration.
In the 2 window `std::string window_choose_name()` client introduces his name.
In the 3 window `User_city_t window_choose_city()` client chooses one of the 5 proposed cities (Moscow, St. Petersburg, Novosibirsk, Yekaterinburg and Dolgoprudny).
In the 4 window `size_t window_show_city(User_city_t user_city)` lient sees the city he has chosen and is proposed to change it if necessary.
In the 5 window `int window_name_error(const std::string& error_text)` client sees an error if the introduced name does not fit.
In the 6 window `int window_main(const std::vector<Weather_info>& arr)` client chooses the number of days.
In the 7-10 windows `void weath_today/tomorrow/3day/5days(const std::vector<Weather_info>& arr)` client is watching the weather for the right number of days.

## Parallel part  

Our project has parallel execution in two threads:

In the first thread `std::thread client_the(client_thread_func)` the client's work code is executed.
In the second thread `std::thread server_the(server_thread_funk)` the server code is running.

The threads are synchronized using the std::mutex mutex to access global data, that is, the `User_info` structure, the `std::vector<Weather_info>` array and command system structure `Shared_cmd`. When changing data or accessing data, the process catches the mutex.

## Using STL and OOP

Our project using STL libraries and basic OOP.
To work with the `Database`, a class was created that connected to an existing database when it was created. the class describes public methods that are used when the client accesses the server.

The parsing class was created, with the field `std::vector<Weather_info> arr`. we preferred `std::vector` from the standard library, because it makes the code more secure, because the responsibility for allocation memory lies not with the programmer. And methods were created to fill this array from json using the library.

Also for working with strings we always use `std::string`.

In visual interfaceclass we use our own class `App::Menu` with sizes, position, color, other formatting and text of menu fields. This class has methods for drawing, aligning and moving along menu items.

## Server work 

When catching the mutex, the server receives a command from the client that must be executed.
If the `NAME_EXIST` command is received, the server checks whether such a name exists in the database (`bool is_name_exist(const User_info& client)` sends an sql query to the database) and writes the result to a global variable `shdata.name_exist`. This action may be delayed because the client may try to enter the name several times.

If the `CITY_BY_NAME` command is received, the server retrieves the user's city from the database (`User_city_t give_city_by_name(const User_info& client)` makes an sql request) and writes city to global data. This happens in the authorization branch. 

If the `CHANGE_CITY` command is received, the server changes the user's city to the database by name (`void change_city(const User_info& client)` makes an sql query and changes the city) and writes it to global data. This happens in the authorization branch if the user wants to change their city.

If the `GIVE_INFO` command is received, the server writes the user's name and city to the global array `std::vector<Weather_info> arr` user's weather( `void give_avg_info_user(const User_info& client, std::vector<Weather_info>& arr)` first calls update_user, which sends an API request, parses json and writes data to the database and extracts the average for each day from them according to the sql query) and writes it to global data. this happens at the moment before the window opens in the weather for different days.



## 📃 How to build our project 

To work under Linux, you need to install libraries:

```
sudo apt install curl   
sudo apt-get install -y libpqxx-dev
sudo apt-get install libsfml-dev
sudo apt install libfmt-dev
```

Building:

```
mkdr build
cd build/
cmake ..
./weather_app
```

### 👨‍💻 Our Contributors

[LizzKuzz](https://github.com/lizz-kuzz)
[KateZap](https://github.com/ZaputriaevaES)
