#include <iostream>
#include <string>
#include <sstream>

#pragma once

struct Error
{
 	std::string message_;
	std::string data_;
 	const char* fileName_;
 	int line_;
 	Error(const std::string& message, const std::string& data, 
			const char* fileName, int line): message_(message), data_(data), fileName_(fileName), line_(line) {}
};



bool isNumber(const std::string& s)
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}


template <class T>
void change_arg(std::string &s, uint32_t k, uint32_t num_of_args, T&& arg)
{
	uint32_t i = 0;
    uint32_t start = -1;
    uint32_t finish = -1;
    while (i < s.length())
    {
        while (s[i] != '{')
        {
            i++;
            if (i == s.length())
                return;
        }

        start = i;
        while (s[i] != '}')
        {
            i++;
            if (i == s.length())
                throw Error("Wrong use of brackets on index:", std::to_string(start), __FILE__, __LINE__);
        }
        finish = i;
		std::string substr = s.substr(start + 1, finish - start - 1);
		if (isNumber(substr) == false) 
			throw Error("Wrong index in brackets:", substr, __FILE__, __LINE__);
		if (std::stoi(substr) == k)
		{
			std::stringstream ss;
			ss << arg;
			s.erase(start, finish - start + 1);
			s.insert(start, ss.str());
		}
		 if (std::stoi(substr) >= num_of_args || std::stoi(substr) < 0)
            throw Error("Index must be in [0, num of formatting arguments], got:", std::to_string(k), __FILE__, __LINE__);
    }
}


template <class T>
void format_arg(std::string &s, uint32_t k, uint32_t num_of_args, T&& arg)
{
	change_arg(s, k, num_of_args, arg);
}


template<class T, class... Args>
void format_arg(std::string &s, uint32_t k, uint32_t num_of_args, T&& arg, Args&&... args)
{	

	change_arg(s, k, num_of_args, arg);
	format_arg(s, k + 1 , num_of_args, std::forward<Args>(args)...);
}


template <class... Args>
std::string format(std::string s, Args&& ... args)
{
	uint32_t num_of_args = sizeof...(Args);
	uint32_t k = 0;
	format_arg(s, k, num_of_args, std::forward<Args>(args)...);
	return s;
}


