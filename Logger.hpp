//
// Created by Keen on 30/01/2022.
//

#ifndef ENEMATA_LOGGER_HPP
#define ENEMATA_LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
public:
    static Logger& getInstance();
    Logger& operator= (const Logger&) = delete;
    Logger(const Logger&) = delete;
    ~Logger();
    void log(const std::string& l_message);
protected:
    Logger();

private:
    std::ofstream m_filestream;
};



#endif //ENEMATA_LOGGER_HPP
/* https://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex
 * class Singleton {
 public:
  static Singleton& Instance() {
    // Since it's a static variable, if the class has already been created,
    // it won't be created again.
    // And it **is** thread-safe in C++11.
    static Singleton myInstance;

    // Return a reference to our instance.
    return myInstance;
  }

  // delete copy and move constructors and assign operators
  Singleton(Singleton const&) = delete;             // Copy construct
  Singleton(Singleton&&) = delete;                  // Move construct
  Singleton& operator=(Singleton const&) = delete;  // Copy assign
  Singleton& operator=(Singleton &&) = delete;      // Move assign

  // Any other public methods.

 protected:
  Singleton() {
    // Constructor code goes here.
  }

  ~Singleton() {
    // Destructor code goes here.
  }

 // And any other protected methods.
}
 *
 *
 * */