//
// Created by Keen on 30/01/2022.
//

#include "Logger.hpp"
#include <iostream>

Logger::Logger() {
    m_filestream.open("Logs.log");
    if(!m_filestream.is_open()){
        std::cout << "warning: could not create Logfile!\n";
    }
}

Logger::~Logger() {
    m_filestream.close();
}

Logger &Logger::getInstance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string &l_message) {
    m_filestream << l_message << "\n";
    m_filestream.flush();
}
