//
// Created by Keen on 23/10/2021.
//
#include "Application.hpp"
#include <stdexcept>
#include <iostream>

int main(){
    Application app;
    try{
        app.run();
    }
    catch(std::exception& l_exception){
        std::cout << l_exception.what();
    }
}