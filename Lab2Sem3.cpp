#include<stdio.h>
#include<iostream>
#include<locale.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>

using namespace std;

void menu() {
	system("cls");
	cout << "Binary images." << endl;
	cout << "1. Refer to the index" << endl;
	cout << "2. Output an image" << endl;
	cout << "3. Sum " << endl;
	cout << "4. Multiplication" << endl;
	cout << "5. Invert image" << endl;
	cout << "6. Coefficient occupancy" << endl;
	cout << "7. Create line" << endl;
	cout << "8. Delete image" << endl;
	cout << "9. Complete" << endl;
}

void menu1() {
	cout << "Fill in the matrix manually?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. Fill false" << endl;
}

template <class T>
class Image {
private:
	T** matrix;
	int maxA, maxB;
	void Print();

public:

	Image(int x, int y);
	Image(const Image& src);
	~Image();
	int GetmaxA() const;
	int GetmaxB() const;

	friend std::ostream& operator<<(std::ostream& out, Image<T>& img)
	{
		img.Print();
		return img;
	}

	bool operator==(const Image<T>& src) const;
	bool operator!=(const Image<T>& src) const;
	T& operator()(int x, int y);
	T operator()(int x, int y) const;
	Image operator+(const Image<T>& src) const;
	Image operator*(const Image<T>& src) const;
	Image operator+(T src) const;
	Image operator*(T src) const;
	Image operator!();
	Image& operator= (const Image& src);
	double AccumulationFactor() const;
};

class EClassException
{
protected:
	char _err[256];
public:
	EClassException(const char* err);
	virtual void Print();
	virtual ~EClassException();
};

	template <class T>
	Image<T>::Image(int MaxA, int MaxB) {
		this->maxA = MaxA;
		this->maxB = MaxB;
		if (maxA <= 0 || maxB <= 0) { throw EClassException("invalid dimension"); }
		matrix = new T * [MaxA];
		for (int i = 0; i < MaxA; i++) {
			matrix[i] = new T[MaxB];
		}
	}

	// Specialization for char
	template <>
	Image<char>::Image(int maxA, int maxB)
	{
		if (maxA <= 0 || maxB <= 0) { throw EClassException("invalid dimension"); }
		matrix = new char* [maxA];
		for (int i = 0; i < maxA; i++)
		{
			matrix[i] = new char[maxB];
		}
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
				matrix[i][j] = '0';
			}
		}
	}

	template <class T>
	int Image<T>::GetmaxA() const { return maxA; }
	template <class T>
	int Image<T>::GetmaxB() const { return maxB; }

	template <class T>
	bool Image<T>::operator==(const Image<T>& src) const
	{
		if (maxA != src.maxA || maxB != src.maxB) { throw EClassException("Can't cmp imgs with different sizes"); } // probably more fair to trow exception 
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
				if (matrix[i][j] != src.matrix[i][j]) { return false; }
			}
		}
		return true;
	}

	template <class T>
	T& Image<T>::operator()(int x, int y)
	{
		if ((x >= maxA || y >= maxB) || (x < 0 || y < 0))
		{
			throw EClassException("invalid index");
		}
		return matrix[x][y];
	}

	template <class T>
	T Image<T>::operator()(int x, int y) const
	{
		if ((x >= maxA || y >= maxB) || (x < 0 || y < 0))
		{
			throw EClassException("invalid index");
		}
		return matrix[x][y];
	}

	template <class T>
	Image<T> Image<T>::operator+(const Image<T>& src) const
	{
		if (maxA != src.maxA || maxB != src.maxB) { throw EClassException("Invalid dimensions of imgs"); }
		Image<T> n(maxA, maxB);
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
				n.matrix[i][j] = matrix[i][j] + src.matrix[i][j];
			}
		}
		return n;
	}


	template <class T>
	Image<T> Image<T>::operator*(const Image<T>& src) const
	{
		if (maxA != src.maxA || maxB != src.maxB) { throw EClassException("Invalid dimensions of imgs"); }
		Image<T> n(maxA, maxB);
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
				n.matrix[i][j] = matrix[i][j] * src.matrix[i][j];
			}
		}
		return n;
	}

	template <class T>
	Image<T> Image<T>::operator*(T src) const
	{
		Image n(maxA, maxB);
	    for (int i = 0; i < maxA; i++)
	    {
	        for (int j = 0; j < maxB; j++)
	        {
	            n.matrix[i][j] = matrix[i][j] * src;
	        }
	    }
	    return n;
	}

	template <class T>
	Image<T> Image<T>::operator!()
	{
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
				if (matrix[i][j] == 0)
				{
					matrix[i][j] == 1;
				}
				else
				{
					matrix[i][j] = 0;
				}
			}
		}
		return *this;
		}


	template <>
		Image<char> Image<char>::operator!()
	{
		for (int i = 0; i < maxA; i++)
		{
			for (int j = 0; j < maxB; j++)
			{
                if (matrix[i][j] == '0')
				{
					matrix[i][j] = 1;
				}
				else
				{
					matrix[i][j] = '0';
				}
			}
		}
	return *this;
	}

	template <class T>
	std::ostream& operator <<(std::ostream& out, Image<T>& img) {
		for (int i = 0; i < img.maxA; i++) {
			for (int j = 0; j < img.maxB; j++) {
				if (img(i, j) == true) out << "1 ";
				else  out << ". ";
			}
			printf("\n");
		}
		return out;
	}

	template <class T>
	Image<T>::~Image()
	{
		for (int i = 0; i < maxA; i++)
		{
			delete[]matrix[i];
		}
		delete[]matrix;
	}
