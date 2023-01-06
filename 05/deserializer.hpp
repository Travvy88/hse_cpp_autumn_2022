#include <string>
#pragma once

class deSerializer
{
    static constexpr char Separator = ' ';
public:
    explicit deSerializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

    template <class T, class... Args>
    Error process( T& value, Args&... args)
    {
        Error err = process(value);
        if (err == Error::CorruptedArchive)
            return err;
        return process(args...);
    }

    Error process(bool &value)
    {
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

    Error process(uint64_t &arg)
    {
		std::string temp;
        in_ >> temp;
		if (!isNumber(temp))
			return Error::CorruptedArchive;
		arg = stoi(temp);
        return Error::NoError;
    }
bool isNumber(const std::string& s)
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}
private:
    std::istream& in_;
    // process использует variadic templates
};
