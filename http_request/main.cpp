#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include "http_request.h"


int main() {

    
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    HTTP::Parsing weather;

    weather.get_buffer();

}

// #ifdef _MSC_VER
// #define _CRT_SECURE_NO_WARNINGS
// #endif
// #pragma comment(lib, "libcurl_imp.lib")

// #include <iostream>
// #include <ctime>
// #include <curl/curl.h>
// #include <json.hp>    

// using json = nlohmann::json;

// size_t writeCallback(char* ptr, int size, int nmemb, void* userdata) {
//     std::string* stream = (std::string*)userdata;
//     int realsize = size * nmemb;
//     stream->append(ptr, realsize);
//     return realsize;
// }

// int main()
// {
//     CURL* curl;
//     CURLcode res;
//     std::string stream;

//     time_t czas;
//     struct tm* data;
//     char godzina[80];
//     time(&czas);
//     data = localtime(&czas);

//     curl = curl_easy_init();
//     if (curl)
//     {
//         curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?q=Gliwice,pl&appid=01bfc1473b89420ac08c560a25c1b535");
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
//         res = curl_easy_perform(curl);

//         if (res != CURLE_OK)
//         {
//             std::cout << "CURL error: " << curl_easy_strerror(res) << std::endl;
//         }
//         else
//         {
//             json weatherData;
//             try
//             {
//                 weatherData = json::parse(stream);
//             }
//             catch (json::parse_error& e)
//             {
//                 std::cout << "Error parsing JSON: " << e.what() << std::endl;
//                 return 1;
//             }

//             try
//             {


//                 double temperature = weatherData["main"]["temp"].get<double>() - 273.15;
//                 double humidity = weatherData["main"]["humidity"];
//                 double pressure = weatherData["main"]["pressure"];
//                 double windSpeed = weatherData["wind"]["speed"];
//                 std::string weatherDescription = weatherData["weather"][0]["description"];
//                 std::string stationName = weatherData["name"];

//                 std::cout << "Aktualne warunki pogodowe" << std::endl;
//                 strftime(godzina, 80, "Stan na godzine: %H:%M", data);
//                 std::cout << godzina;

//                 std::cout << "\nTemperatura: " << temperature << " stopni Celsjusza" << std::endl;
//                 std::cout << "Wilgotnosc: " << humidity << "%" << std::endl;
//                 std::cout << "Cisnienie: " << pressure << "hPa" << std::endl;
//                 std::cout << "Opis pogody: " << weatherDescription << std::endl;
//                 std::cout << "Predkosc wiatru: " << windSpeed << " m/s" << std::endl;
//                 std::cout << "Stacja badawcza: " << stationName << std::endl;
//             }
//             catch (json::exception& e)
//             {
//                 std::cout << "Error: " << e.what() << std::endl;
//             }
//         }
//         curl_easy_cleanup(curl);
//     }
//     return 0;
// }