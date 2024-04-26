#pragma once 

#include <pqxx/pqxx>

// using namespace pqxx; remember!!

class Database {
    pqxx::work request;

    Database();

}//namespace Database