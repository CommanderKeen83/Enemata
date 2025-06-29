//
// Created by CommanderKeen on 14.10.24.
//
module;
#include <string>
#include <fstream>
export module Logger;


export class Logger{
public:

    ~Logger(){
        m_file.close();
    }

    static Logger& getInstance(){
        static Logger logger;
        return logger;
    }
    void log(const std::string& l_message){
        m_file << l_message << "\n";
        m_file.flush();
    }
private:
    Logger(){
        m_file.open("Logs.log");
        if(!m_file.is_open()){
            throw std::runtime_error("Error in Logger::Logger - could not create File Logs.log!");
        }
    }
    std::ofstream m_file;
};