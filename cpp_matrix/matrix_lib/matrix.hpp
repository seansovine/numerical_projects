#include <iostream>
#include <iomanip>
#include <sstream>

/* ---- Forward declarations. ---- */

template <typename T>
class Matrix;

template <typename T>
Matrix<T> operator*(const T &, const Matrix<T> &);

#ifndef MATRIX_IMPL
#define MATRIX_IMPL

/* ---- Matrix declaration. ---- */

template <typename T>
class Matrix
{
	// Store row-major.
	T *data;

public:
	const unsigned rows;
	const unsigned cols;

public:
	Matrix(const unsigned &, const unsigned &);

	// Explicit deep copy constructor.
	Matrix(const Matrix<T> &);

	// Explicit move constructor;
	Matrix(Matrix<T> &&other) noexcept;

	~Matrix();

	// See: https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op

	T &operator()(unsigned row, unsigned col);		// To modify the value.
	T operator()(unsigned row, unsigned col) const; // For use with const Matrixes.

	explicit operator std::string() const;

	template <typename _> // Is this right?
	friend Matrix<T> operator*(const T &a, const Matrix<T> &m);
};

/* ---- Matrix implementation. ---- */

template <typename T>
T &Matrix<T>::operator()(unsigned row, unsigned col)
{
	// Row-major access.
	return data[col + row * cols];
}

template <typename T>
T Matrix<T>::operator()(unsigned row, unsigned col) const
{
	// Row-major access.
	return data[col + row * cols];
}

template <typename T>
Matrix<T>::operator std::string() const
{
	// Compute max width for alignment.

	unsigned max_width = 0; // Could do per-column.
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			const T &entry = (*this)(i, j);
			std::string as_string = std::to_string(entry);
			unsigned width = static_cast<unsigned>(as_string.length());
			max_width = (width > max_width) ? width : max_width;
		}
	}

	// Build string.

	std::stringstream oss{};
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			const T &entry = (*this)(i, j);
			oss << std::setw(max_width + 1) << entry;
		}
		if (i < rows - 1)
			oss << std::endl;
	}

	return oss.str();
}

// Constructors.
template <typename T>
Matrix<T>::~Matrix()
{
	delete[] data;
}

template <typename T>
Matrix<T>::Matrix(const unsigned &rows, const unsigned &cols) : rows{rows}, cols{cols}
{
	const unsigned int num_entries = rows * cols;
	data = new T[num_entries]{};
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept : data{other.data}, rows{other.rows}, cols{other.cols}
{
	other.data = nullptr;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : rows{other.rows}, cols{other.cols}
{
	const unsigned int num_entries = rows * cols;
	data = new T[num_entries]{};
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < cols; j++)
		{
			data[j + i * cols] = other(i, j);
		}
	}
}

// Not a member function.

template <typename T>
Matrix<T> operator*(const T &a, const Matrix<T> &m)
{
	Matrix<T> result{m.rows, m.cols};
	for (unsigned i = 0; i < m.rows; i++)
	{
		for (unsigned j = 0; j < m.cols; j++)
		{
			result(i, j) = a * m(i, j);
		}
	}
	return result; // Returns new Matrix object.
}

#endif