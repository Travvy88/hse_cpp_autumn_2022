#include <iostream>


class Matrix
{
    class ProxyRow
    {
    private:
        int32_t *data_;
    public:
		size_t cols;

		ProxyRow(){};
        ProxyRow(size_t cols) 
		{
			data_ = new int32_t [cols];
			this->cols = cols;
		}

        int32_t& operator[](size_t j)
        {
            return data_[j];
        }
    };


public:
	~Matrix()
	{
		delete rows_;
	}

	Matrix(){}
    Matrix(size_t rows, size_t cols)
	{
		rows_ = new ProxyRow[rows];
		for (size_t i=0; i < rows; i++)
			rows_[i] = ProxyRow(cols);
		this->rows = rows;
	}

	size_t getRows() const
	{
		return this->rows;
	}

	size_t getCols() const
	{
		return this->rows_[0].cols;
	}

    ProxyRow& operator[](size_t i) const
    {
        return rows_[i];
    }

	Matrix&  operator*=(int32_t x)
	{
		for (size_t i = 0; i < getRows(); i++)
			for (size_t j = 0; j < getCols(); j++)
				(*this)[i][j] *= x;// * x;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream &out, const Matrix& m);

	Matrix operator+(const Matrix& m) const
	{
		if (this->getCols() != m.getCols() and this->getRows() != m.getRows())
			throw std::out_of_range("matricies shapes are not equal");

		Matrix result(m.getRows(), m.getCols());
		 for (size_t i = 0; i < getRows(); i++)
            for (size_t j = 0; j < getCols(); j++)
				result[i][j] = (*this)[i][j] + m[i][j];

		return result; 
	}

	bool operator==(const Matrix& m)
	{
		 if (this->getCols() != m.getCols() and this->getRows() != m.getRows())
            throw std::out_of_range("matricies shapes are not equal");
		for (size_t i = 0; i < getRows(); i++)
            for (size_t j = 0; j < getCols(); j++)
				if ((*this)[i][j] != m[i][j])
					return false

		return true
	}

private:
	size_t rows;
    ProxyRow *rows_;
};

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


int main()
{
	Matrix m(2, 2);
	m[0][0] = 4;
	m[0][1] = 4;
	m[1][0] = 4;
	m[1][1] = 4;

	std::cout << m[0][1] << std::endl;
	std::cout << m.getRows() << std::endl;
	std::cout << m.getCols() << std::endl;
	m *= 2;
	std::cout << "multiply 2" << std::endl;
	std::cout << m[0][0] << std::endl;
	std::cout << m[0][1] << std::endl;
	std::cout << m;
	std::cout << "plus plus" << std::endl;
	Matrix n(2, 2);
	
    n[0][0] = 3;
    n[0][1] = 3;
    n[1][0] = 3;
    n[1][1] = 3;
	
	auto x = n + m;
	std::cout << x << std::endl;
	
	


}

