#include <string>
#pragma once


class TokenParser {
private:
    uint64_t (*DigitTokenCallback)(uint64_t) = nullptr; 
    std::string (*LetterTokenCallback)(std::string) = nullptr;
    std::string (*StartCallback)(std::string) = nullptr;
    std::string (*EndCallback)(std::string) = nullptr;

public:
	TokenParser() = default;
	void SetDigitTokenCallback(uint64_t (*func)(uint64_t));
	void SetLetterTokenCallback(std::string (*func)(std::string));
	void SetStartCallback(std::string (*func)(std::string));
	void SetEndCallback(std::string (*func)(std::string));
	void SetCallback(std::string (*func)(std::string));
	 
	uint64_t convert(std::string);
	bool isDigit(std::string);
	std::string Parse(const std::string & );
};
