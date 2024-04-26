#define CURL_STATICLIB

#include <iostream>
#include <curl/curl.h>
#include "http_request.h"
#include "json_parsing.h"
#include "database.h"

int main() {
    std::string readBuffer;

    HTTP::Request weather;
    weather.get_buffer_from_api(); //add here coord diffrent countries + bd

    Parsing::parse(weather.buffer);

    pqxx::connection c{"postgresql://lizzkuzz:1511@localhost/testdb"};
    //   pqxx::connection c{"postgresql://accounting@localhost/company"};
    pqxx::work txn{c};

  // For querying just one single value, the transaction has a shorthand method
  // query_value().
  //
  // Use txn.quote() to escape and quote a C++ string for use as an SQL string
  // in a query's text.
    pqxx::result r{txn.exec("SELECT temp FROM table_temp;")};
    for (auto row : r) {
        std::cout
      // Address column by name.  Use c_str() to get C-style string.
        << row[0]
      // Address column by zero-based index.  Use as<int>() to parse as int.
        << std::endl;
    }

}
