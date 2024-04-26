#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include "http_request.h"
#include "json_parsing.h"
#include "database.h"

int main() {
    // std::string readBuffer;

    // HTTP::Request weather;
    // weather.get_buffer_from_api(); //add here coord diffrent countries + bd

    // Parsing::parse(weather.buffer);

    pqxx::connection weather_database{"postgresql://lizzkuzz:1511@localhost/testdb"};
    //   pqxx::connection c{"postgresql://accounting@localhost/company"};
    pqxx::work request{weather_database};

  // For querying just one single value, the transaction has a shorthand method
  // query_value().
  //
  // Use txn.quote() to escape and quote a C++ string for use as an SQL string
  // in a query's text.
    std::string city = "moscow";
    std::string sql_request = "select city, temp from table_temp where table_temp.city = '" + city + "';";
    pqxx::result res_request{request.exec(sql_request.c_str())};
    std::cout << res_request.empty() << std::endl;
    for (auto row : res_request) {
        std::cout 
      // Address column by name.  Use c_str() to get C-style string.
        << row[0] << " " << row[1]
      // Address column by zero-based index.  Use as<int>() to parse as int.
        << std::endl;
    }

}
