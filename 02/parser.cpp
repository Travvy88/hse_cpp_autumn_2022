#include "parser.hpp"


void TokenParser::SetDigitTokenCallback(uint64_t (*func)(uint64_t i)) {
    DigitTokenCallback = func;
}

void TokenParser::TokenParser::SetLetterTokenCallback(std::string (*func)(std::string str)) {
    LetterTokenCallback = func;
}

void TokenParser::SetStartCallback(std::string (*func)(std::string str)) {
	StartCallback = func;
}

void TokenParser::SetEndCallback(std::string (*func)(std::string str)) {
    EndCallback = func;
}

void TokenParser::SetCallback(std::string (*func)(std::string str)) {
    Callback = func;
}

uint64_t TokenParser::convert(std::string str) {
    uint64_t i = std::stoi(str);
    return i;
}

bool TokenParser::isDigit(std::string str) {
    for (auto ch : str) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

std::string TokenParser::Parse(const std::string & str)
    {
        std::string new_str = "";
        std::string work_str = str;
        if (StartCallback != nullptr)
             work_str = StartCallback( work_str); //callback to string before parsing
        std::string word = "";
        work_str += " ";
        for (auto ch : work_str) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                if (Callback != nullptr) // token callback
                    word = Callback(word);
                if (isDigit(word) and DigitTokenCallback != nullptr) { // only for digits token
                    try{ // try to fetch into uint64_t size
                        uint64_t word_num = std::stoul(word);
                        word_num = DigitTokenCallback(word_num);
                        word = std::to_string(word_num);
                    }
                    catch (...) {
                        if (LetterTokenCallback != nullptr)
                            word = LetterTokenCallback(word);
                    }
                }
                else if (LetterTokenCallback != nullptr) // only for letters token
                    word = LetterTokenCallback(word);
                new_str = new_str + " " + word;
                word = "";
            }  else {
                word = word + ch;
            }
        }
    new_str = new_str + " " + word;
    if (EndCallback != nullptr)
        new_str = EndCallback(new_str); // callback to result string after parsing
    return new_str;
    }
