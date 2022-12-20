#pragma once
#include <iostream>
#include <math.h>
#include <iomanip>

class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    void Print();
    ~EClassException();
};

EClassException::EClassException(const char* err)
{
    strncpy_s(_err, err, 255);
    _err[255] = 0;
}
void EClassException::Print()
{
    std::cout << _err << std::endl;
}
EClassException::~EClassException() {}

template <typename T>
class BinaryImg
{
private:
    T** matrix;
    int row;
    int col;
    BinaryImg<T> And(T rhs) const
    {
        BinaryImg<T> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = matrix[i][j] * rhs;
            }
        }
        return result;
    }
    BinaryImg<T> Or(T rhs) const
    {
        BinaryImg<T> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = matrix[i][j] + rhs;
            }
        }
        return result;
    }
    BinaryImg<T> And(const BinaryImg<T>& src) const
    {
        if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of images"); }
        BinaryImg<T> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = matrix[i][j] * src.matrix[i][j];
            }
        }
        return result;
    }
    BinaryImg<T> Or(const BinaryImg<T>& src) const
    {
        if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of images"); }
        BinaryImg<T> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = matrix[i][j] + src.matrix[i][j];
            }
        }
        return result;
    }


public:
    BinaryImg(int x, int y)
    {
        if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
        row = x;
        col = y;
        matrix = new T * [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new T[col]{};
        }
    }
    BinaryImg(const BinaryImg<T>& src)
    {
        row = src.row;
        col = src.col;
        matrix = new T * [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new T[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = src.matrix[i][j];
            }
        }
    }

    ~BinaryImg()
    {
        for (int i = 0; i < row; i++)
        {
            delete[]matrix[i];
        }
        delete[]matrix;
    }
    int GetRow() const { return row; }
    int GetCol() const { return col; }
    friend std::ostream& operator<<(std::ostream& os, BinaryImg<T>& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                std::cout << obj.matrix[i][j] << std::setw(2);
            }
            std::cout << "\n";
        }
        return os;
    }
    bool operator==(const BinaryImg<T>& src) const
    {
        if (row != src.row || col != src.col) { return false; }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] != src.matrix[i][j]) { return false; }
            }
        }
        return true;
    }
    bool operator!=(const BinaryImg<T>& src) const
    {
        return !(*this == src);
    }
    T& operator()(int x, int y)
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return matrix[x][y];
    }
    T operator()(int x, int y) const
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return matrix[x][y];
    }
    BinaryImg<T> operator+(const BinaryImg<T>& src) const
    {
        return this->Or(src);
    }
    BinaryImg<T> operator*(const BinaryImg<T>& src) const
    {
        return this->And(src);
    }
    BinaryImg<T> operator+(T rhs) const
    {
        return this->Or(rhs);
    }
    BinaryImg<T> operator*(T rhs) const
    {
        return this->And(rhs);
    }
    BinaryImg<T> operator!()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][j] = std::numeric_limits<T>::max();
                }
                else
                {
                    matrix[i][j] = 0;
                }
            }
        }
        return *this;
    }
    BinaryImg<T>& operator= (const BinaryImg<T>& src) {
        if (this == (&src)) { return *this; }
        if (row == src.row && col == src.col)
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = src.matrix[i][j];
                }
            }
            return *this;
        }

        for (int i = 0; i < row; i++)
        {
            delete[]matrix[i];
        }
        delete[]matrix;

        row = src.row;
        col = src.col;

        matrix = new T * [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new T[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = src.matrix[i][j];
            }
        }
        return *this;
    }

    double Coeff() const
    {
        int k = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j]) { k++; }
            }
        }
        double res = (double)k / (row * col);
        return res;
    }
    friend BinaryImg<T> operator*(T rhs, const BinaryImg<T>& src)
    {
        return src.And(rhs);
    }
    friend BinaryImg<T> operator+(T rhs, const BinaryImg<T>& src)
    {
        return src.Or(rhs);
    }
};


template <>
class BinaryImg<char>
{
private:
    char** matrix;
    int row;
    int col;
    BinaryImg<char> And(char rhs) const
    {
        BinaryImg<char> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = (int)matrix[i][j] * (int)rhs;
            }
        }
        return result;
    }
    BinaryImg<char> Or(char rhs) const
    {
        BinaryImg<char> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = (int)matrix[i][j] + (int)rhs;
            }
        }
        return result;
    }
    BinaryImg<char> And(const BinaryImg<char>& src) const
    {
        if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of images"); }
        BinaryImg<char> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = (int)matrix[i][j] * (int)src.matrix[i][j];
            }
        }
        return result;
    }
    BinaryImg<char> Or(const BinaryImg<char>& src) const
    {
        if (row != src.row || col != src.col) { throw EClassException("Invalid dimensions of images"); }
        BinaryImg<char> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.matrix[i][j] = (int)matrix[i][j] + (int)src.matrix[i][j];
            }
        }
        return result;
    }

public:
    BinaryImg(int x, int y)
    {
        if (x <= 0 || y <= 0) { throw EClassException("invalid dimension"); }
        row = x;
        col = y;
        matrix = new char* [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new char[col];
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = '0';
            }
        }
    }
    BinaryImg(const BinaryImg<char>& src)
    {
        row = src.row;
        col = src.col;
        matrix = new char* [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new char[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = src.matrix[i][j];
            }
        }
    }
    ~BinaryImg()
    {
        for (int i = 0; i < row; i++)
        {
            delete[]matrix[i];
        }
        delete[]matrix;
    }
    int GetRow() const { return row; }
    int GetCol() const { return col; }
    friend std::ostream& operator<<(std::ostream& os, BinaryImg<char>& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                std::cout << obj.matrix[i][j] << std::setw(2);
            }
            std::cout << "\n";
        }
        return os;
    }
    bool operator==(const BinaryImg<char>& src) const
    {
        if (row != src.row || col != src.col) { return false; }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] != src.matrix[i][j]) { return false; }
            }
        }
        return true;
    }
    bool operator!=(const BinaryImg<char>& src) const
    {
        return !(*this == src);
    }
    char& operator()(int x, int y)
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return matrix[x][y];
    }
    char operator()(int x, int y) const
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return matrix[x][y];
    }
    BinaryImg<char> operator+(const BinaryImg<char>& src) const
    {
        return this->Or(src);
    }
    BinaryImg<char> operator*(const BinaryImg<char>& src) const
    {
        return this->And(src);
    }
    BinaryImg<char> operator+(char rhs) const
    {
        return this->Or(rhs);
    }
    BinaryImg<char> operator*(char rhs) const
    {
        return this->And(rhs);
    }
    BinaryImg<char> operator!()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] == '0')
                {
                    matrix[i][j] = std::numeric_limits<char>::max();
                }
                else
                {
                    matrix[i][j] = '0';
                }
            }
        }
        return *this;
    }
    BinaryImg<char>& operator= (const BinaryImg<char>& src)
    {
        if (this == (&src)) { return *this; }
        if (row == src.row && col == src.col)
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = src.matrix[i][j];
                }
            }
            return *this;
        }

        for (int i = 0; i < row; i++)
        {
            delete[]matrix[i];
        }
        delete[]matrix;

        row = src.row;
        col = src.col;

        matrix = new char* [row];
        for (int i = 0; i < row; i++)
        {
            matrix[i] = new char[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[i][j] = src.matrix[i][j];
            }
        }
        return *this;
    }
    double Coeff() const
    {
        int k = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (matrix[i][j] != '0') { k++; }
            }
        }
        double res = (double)k / (row * col);
        return res;
    }
    friend BinaryImg<char> operator*(char rhs, const BinaryImg<char>& src)
    {
        return src.And(rhs);
    }
    friend BinaryImg<char> operator+(char rhs, const BinaryImg<char>& src)
    {
        return src.Or(rhs);
    }
};