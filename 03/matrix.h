#include <iostream>
#pragma once

class Matrix
{
    class ProxyRow{
    private:
        int32_t *data_;
    public:
        size_t cols;

        ProxyRow() {};
        void initialize(size_t);
        int32_t& operator[](size_t);

    };
public:
    ~Matrix();
    Matrix() {};
    Matrix(size_t, size_t);
    size_t getRows() const;
    size_t getCols() const;
    ProxyRow& operator[](size_t) const;
    Matrix&  operator*=(int32_t);
    friend std::ostream& operator<<(std::ostream, const Matrix&);
    Matrix operator+(const Matrix&) const;
    bool operator==(const Matrix&);

private:
    size_t rows;
    ProxyRow *rows_;
};
