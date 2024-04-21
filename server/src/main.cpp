#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include "http_request.h"
#include "json_parsing.h"

int main() {
    std::string readBuffer;

    HTTP::Request weather;
    weather.get_buffer_from_api(); //add here coord diffrent countries

    Parsing::parse(weather.buffer);

}
