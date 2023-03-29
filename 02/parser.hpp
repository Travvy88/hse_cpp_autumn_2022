#include <string>
#pragma once

using digit_func = uint64_t (*)(uint64_t i);
using letter_func = std::string (*)(std::string str);

class TokenParser {
private:
    uint64_t (*DigitTokenCallback)(uint64_t) = nullptr; 
    std::string (*LetterTokenCallback)(std::string) = nullptr;
    std::string (*StartCallback)(std::string) = nullptr;
    std::string (*EndCallback)(std::string) = nullptr;

public:
	TokenParser() = default;
	void SetDigitTokenCallback(digit_func);
	void SetLetterTokenCallback(letter_func);
	void SetStartCallback(letter_func);
	void SetEndCallback(letter_func);
	 
	uint64_t convert(std::string);
	bool isDigit(std::string);
	std::string Parse(const std::string & );
};
