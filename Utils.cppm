//
// Created by CommanderKeen on 14.10.24.
//


module;
#include <string>
#include <stdexcept>
#include <iostream>
#include <ctype.h>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

export module Utils;

export namespace Utils {
    std::string toLower(const std::string& l_str){
        std::string result = l_str;
        for(auto& chr : result){
            chr = (char)tolower(chr);
        }
        return result;
    }


    std::string get_project_path() {
        const int MAX_PATH_LENGTH = 256;
		char temp_result[MAX_PATH_LENGTH];
        std::string result;
#ifdef _WIN32

		DWORD size = GetModuleFileNameA(NULL, temp_result, MAX_PATH_LENGTH);
		if (size > 0) {
			std::string substring{ temp_result };
			substring = substring.substr(0, substring.find_last_of('\\'));
			substring = substring.substr(0, substring.find_last_of('\\'));
			result = substring;
		}
		else {
			throw std::runtime_error("Error in Utils::get_project_path() - could not retrieve working path!");
		}
#elif __APPLE__
        char currentPath[PATH_MAX];
        if (getcwd(currentPath, sizeof(currentPath)) != nullptr) {
            std::string subStr{currentPath};
            subStr = subStr.substr(0, subStr.find_last_of('/'));
            result = subStr;
            result.append("/");
        }
        else {
            throw std::runtime_error("Error in Utils::get_project_path() - could not retrieve working path!");
        }
#endif
        return result;
    } // end of std::string get_project_path()

    std::string formatPath(const std::string& l_str) {
        std::string result = l_str;
#ifdef _WIN32
    std::replace_if(result.begin(), result.end(), [](char c)-> bool  {
        return (c == '/' || c == '\\');
    }, '\\');

#elif __APPLE__
        std::replace_if(result.begin(), result.end(), [](char c)-> bool  {
        return (c == '/' || c == '\\');
    }, '/');
#endif
        return result;
    }
}// end of namespace Utils