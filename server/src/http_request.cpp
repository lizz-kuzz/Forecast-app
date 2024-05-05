#include "http_request.h" 


static size_t write_data(char* ptr, size_t size, size_t nmemb, void* data) {
    if (data) {
        ((std::string*)data)->append(ptr, size * nmemb);
        return size * nmemb;
    } else {
        std::cout << "error";
    }
    
    return 0;
} 

void HTTP::Request::get_buffer_from_api(double lat, double lon) {
    CURL *curl;
    CURLcode res;
    std::string api_request = "api.openweathermap.org/data/2.5/forecast?lat=" + std::to_string(lat) + "&lon=" + std::to_string(lon)
                              + "&exclude=daily&current.temp=Celsius&units=metric&appid=464a485473994b656c2f1419b57a028a";
    // "api.openweathermap.org/data/2.5/forecast?lat=55.939831&lon=37.503434&exclude=daily&current.temp=Celsius&units=metric&appid=464a485473994b656c2f1419b57a028a";
    std::cout << api_request << std::endl;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_request.c_str());
        /* tell it to "upload" to the URL */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        /* set where to read from */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed:" << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }   
}


