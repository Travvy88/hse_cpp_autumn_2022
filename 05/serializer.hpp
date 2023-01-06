#include "error.h"
#pragma once

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

    template <class T, class... Args>
    Error process(const T& value, const Args&... args)
    {
        Error err = process(value);
        return process(args...);
    }

    Error process(const bool &arg)
    {
        if (arg == true)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;

        return Error::NoError;
    }

    Error process(const uint64_t &arg)
    {
        out_ << arg << Separator;
        return Error::NoError;
    }
private:
    std::ostream& out_;
    // process использует variadic templates
};
