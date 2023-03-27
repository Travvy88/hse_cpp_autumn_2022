#include <iostream>
#include "matrix.h"


void Matrix::ProxyRow::initialize(size_t cols)
{
    data_ = new int32_t [cols];
    this->cols = cols;
}

int32_t& Matrix::ProxyRow::operator[](size_t j)
{
    if (j >= cols)
        throw std::out_of_range("Columns index out of range");
    return data_[j];
}

Matrix::~Matrix()
{
    delete rows_;
}

Matrix::Matrix(size_t rows, size_t cols)
{
    rows_ = new Matrix::ProxyRow[rows];
    for (size_t i=0; i < rows; i++)
        rows_[i].initialize(cols);
    this->rows = rows;
}

size_t Matrix::getRows() const
{
    return this->rows;
}

size_t Matrix::getCols() const
{
    return this->rows_[0].cols;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) const
{
    if (i >= rows)
        throw std::out_of_range("Rows index out of range");
    return rows_[i];
}

Matrix&  Matrix::operator*=(int32_t x)
{
    for (size_t i = 0; i < getRows(); i++)
        for (size_t j = 0; j < getCols(); j++)
            (*this)[i][j] *= x;// * x;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const
{
    if (this->getCols() != m.getCols() or this->getRows() != m.getRows())
        throw std::out_of_range("matricies shapes are not equal");

    Matrix result(m.getRows(), m.getCols());
     for (size_t i = 0; i < getRows(); i++)
        for (size_t j = 0; j < getCols(); j++)
            result[i][j] = (*this)[i][j] + m[i][j];

    return result;
}

bool Matrix::operator==(const Matrix& m)
{
     if (this->getCols() != m.getCols() and this->getRows() != m.getRows())
        throw std::out_of_range("matricies shapes are not equal");
    for (size_t i = 0; i < getRows(); i++)
        for (size_t j = 0; j < getCols(); j++)
            if ((*this)[i][j] != m[i][j])
                return false;

    return true;
}

std::ostream& operator<<(std::ostream &out, const Matrix& m)
    {
        for (size_t i = 0; i < m.getRows(); i++)
        {
            for (size_t j = 0; j <m.getCols(); j++)
            {
                out << " " << m[i][j];
            }
            out << std::endl;
        }
    return out;
    }

