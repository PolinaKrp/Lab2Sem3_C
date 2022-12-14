#pragma once
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

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
    cout << _err << endl;
}
EClassException::~EClassException() {}

template <typename T>
class BinaryImg
{
private:
    T** array;
    int row;
    int col;

    BinaryImg<T> And(T rhs) const
    {
        BinaryImg<T> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.array[i][j] = array[i][j] * rhs;
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
                result.array[i][j] = array[i][j] + rhs;
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
                result.array[i][j] = array[i][j] * src.array[i][j];
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
                result.array[i][j] = array[i][j] + src.array[i][j];
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
        array = new T * [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new T[col]{};
        }
    }

    BinaryImg(const BinaryImg<T>& src)
    {
        row = src.row;
        col = src.col;
        array = new T * [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new T[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = src.array[i][j];
            }
        }
    }

    ~BinaryImg()
    {
        for (int i = 0; i < row; i++)
        {
            delete[]array[i];
        }
        delete[]array;
    }

    int GetRow() const { return row; }
    int GetCol() const { return col; }

    friend ostream& operator<<(std::ostream& os, BinaryImg<T>& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                cout << obj.array[i][j] << std::setw(2);
            }
            cout << "\n";
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
                if (array[i][j] != src.array[i][j]) { return false; }
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
        return array[x][y];
    }

    T operator()(int x, int y) const
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return array[x][y];
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
                if (array[i][j] == 0)
                {
                    array[i][j] = std::numeric_limits<T>::max();
                }
                else
                {
                    array[i][j] = 0;
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
                    array[i][j] = src.array[i][j];
                }
            }
            return *this;
        }

        for (int i = 0; i < row; i++)
        {
            delete[]array[i];
        }
        delete[]array;

        row = src.row;
        col = src.col;

        array = new T * [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new T[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = src.array[i][j];
            }
        }
        return *this;
    }

    double FillFactor() const
    {
        int k = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (array[i][j]) { k++; }
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

// Specialization for char
template <>
class BinaryImg<char>
{
private:
    char** array;
    int row;
    int col;
    BinaryImg<char> And(char rhs) const
    {
        BinaryImg<char> result(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                result.array[i][j] = (int)array[i][j] * (int)rhs;
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
                result.array[i][j] = (int)array[i][j] + (int)rhs;
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
                result.array[i][j] = (int)array[i][j] * (int)src.array[i][j];
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
                result.array[i][j] = (int)array[i][j] + (int)src.array[i][j];
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
        array = new char* [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new char[col];
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = '0';
            }
        }
    }

    BinaryImg(const BinaryImg<char>& src)
    {
        row = src.row;
        col = src.col;
        array = new char* [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new char[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = src.array[i][j];
            }
        }
    }

    ~BinaryImg()
    {
        for (int i = 0; i < row; i++)
        {
            delete[]array[i];
        }
        delete[]array;
    }

    int GetRow() const { return row; }
    int GetCol() const { return col; }

    friend std::ostream& operator<<(std::ostream& os, BinaryImg<char>& obj)
    {
        for (int i = 0; i < obj.row; i++)
        {
            for (int j = 0; j < obj.col; j++)
            {
                std::cout << obj.array[i][j] << std::setw(2);
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
                if (array[i][j] != src.array[i][j]) { return false; }
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
        return array[x][y];
    }

    char operator()(int x, int y) const
    {
        if ((x >= row || y >= col) || (x < 0 || y < 0))
        {
            throw EClassException("invalid index");
        }
        return array[x][y];
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
                if (array[i][j] == '0')
                {
                    array[i][j] = std::numeric_limits<char>::max();
                }
                else
                {
                    array[i][j] = '0';
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
                    array[i][j] = src.array[i][j];
                }
            }
            return *this;
        }

        for (int i = 0; i < row; i++)
        {
            delete[]array[i];
        }
        delete[]array;

        row = src.row;
        col = src.col;

        array = new char* [row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new char[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                array[i][j] = src.array[i][j];
            }
        }
        return *this;
    }

    double FillFactor() const
    {
        int k = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (array[i][j] != '0') { k++; }
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