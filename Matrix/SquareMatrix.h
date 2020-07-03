#pragma once

#include <cmath>
#include "ColumnMatrix.h"

template<std::size_t N>
class SquareMatrix;

template<std::size_t N>
SquareMatrix<N> operator*(const SquareMatrix<N>& m, double k);
template<std::size_t N>
SquareMatrix<N> operator*(double k, const SquareMatrix<N>& m);
template<std::size_t N>
std::ostream& operator<<(std::ostream& s, const SquareMatrix<N>& m);
template<std::size_t N>
std::istream& operator>>(std::istream& s, SquareMatrix<N>& m);
template<std::size_t N>
SquareMatrix<N - 1> smaller(const SquareMatrix<N>& m, std::size_t deleted_row, std::size_t deleted_col);
template<std::size_t N>
double det(const SquareMatrix<N>& m);
template<std::size_t N>
SquareMatrix<N> transponse(const SquareMatrix<N>& m);
template<std::size_t N>
SquareMatrix<N> invertible(const SquareMatrix<N>& m);

template<std::size_t N>
class SquareMatrix
{
	double** matrix;
	mutable double determinant;

	void destroy();
	void resetDeterminant();
public:
	SquareMatrix();
	SquareMatrix(const SquareMatrix& other);
	SquareMatrix(SquareMatrix&& other) noexcept;
	SquareMatrix& operator=(SquareMatrix&& other) noexcept;
	~SquareMatrix();

	SquareMatrix(std::size_t k);
	SquareMatrix(const std::initializer_list<std::initializer_list<double>>& init_list);
	SquareMatrix& operator=(const SquareMatrix& other);
	SquareMatrix& operator+=(const SquareMatrix& other);
	SquareMatrix operator+(const SquareMatrix& other) const;
	SquareMatrix& operator-=(const SquareMatrix& other);
	SquareMatrix operator-(const SquareMatrix& other) const;
	SquareMatrix& operator*=(const SquareMatrix& other);
	SquareMatrix operator*(const SquareMatrix& other) const;
	SquareMatrix& operator*=(double k);
	SquareMatrix& operator/=(double d);
	SquareMatrix operator/(double d) const;
	ColumnMatrix<N> operator*(const ColumnMatrix<N>& k);
	template<std::size_t U>
	friend SquareMatrix<U> operator*(const SquareMatrix<U>& m, double k);
	template<std::size_t U>
	friend SquareMatrix<U> operator*(double k, const SquareMatrix<U>& m);

	double* operator[](std::size_t i);
	double operator[](std::size_t i) const;
	template<std::size_t U>
	friend std::ostream& operator<<(std::ostream& s, const SquareMatrix<U>& m);
	template<std::size_t U>
	friend std::istream& operator>>(std::istream& s, SquareMatrix<U>& m);
	
	template<std::size_t U>
	friend SquareMatrix<U - 1> smaller(const SquareMatrix<U>& m, std::size_t deleted_row, std::size_t deleted_col);
	friend double det<N>(const SquareMatrix& m);
	friend SquareMatrix transponse<N>(const SquareMatrix& m);
	friend SquareMatrix invertible<N>(const SquareMatrix& m);
};

template<std::size_t N>
void SquareMatrix<N>::destroy()
{
	if (matrix != nullptr)
	{
		for (size_t i = 0; i < N; ++i)
			delete[] matrix[i];
		delete[] matrix;
	}
}

template<std::size_t N>
void SquareMatrix<N>::resetDeterminant()
{
	determinant = std::nan("");
}

template<std::size_t N>
SquareMatrix<N>::SquareMatrix()
: determinant(std::nan(""))
{
	matrix = new double* [N];
	for (size_t i = 0; i < N; ++i)
		matrix[i] = new double[N];
}

template<std::size_t N>
SquareMatrix<N>::SquareMatrix(const SquareMatrix& other)
: SquareMatrix()
{
	*this = other;
}

template<std::size_t N>
SquareMatrix<N>::SquareMatrix(SquareMatrix&& other) noexcept
: SquareMatrix()
{
	*this = std::move(other);
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator=(SquareMatrix&& other) noexcept
{
	destroy();
	matrix = other.matrix;
	other.matrix = nullptr;
	determinant = other.determinant;
	return *this;
}

template<std::size_t N>
SquareMatrix<N>::~SquareMatrix()
{
	destroy();
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator=(const SquareMatrix& other)
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] = other.matrix[i][j];
	determinant = other.determinant;
	return *this;
}

template<std::size_t N>
SquareMatrix<N>::SquareMatrix(std::size_t k)
: SquareMatrix()
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] = i != j ? 0 : k;
	determinant = pow(k, N);
}

template<std::size_t N>
SquareMatrix<N>::SquareMatrix(const std::initializer_list<std::initializer_list<double>>& init_list)
: SquareMatrix()
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] = *((init_list.begin() + i)->begin() + j);
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator+=(const SquareMatrix& other)
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] += other.matrix[i][j];
	resetDeterminant();
	return *this;
}

template<std::size_t N>
SquareMatrix<N> SquareMatrix<N>::operator+(const SquareMatrix& other) const
{
	SquareMatrix result = *this;
	result += other;
	return result;
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator-=(const SquareMatrix& other)
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] -= other.matrix[i][j];
	resetDeterminant();
	return *this;
}

template<std::size_t N>
SquareMatrix<N> SquareMatrix<N>::operator-(const SquareMatrix& other) const
{
	SquareMatrix result = *this;
	result -= other;
	return result;
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator*=(const SquareMatrix& other)
{
	SquareMatrix<N> tmp;
	tmp = *this * other;
	*this = std::move(tmp);
	return *this;
}

template<std::size_t N>
SquareMatrix<N> SquareMatrix<N>::operator*(const SquareMatrix& other) const
{
	SquareMatrix result;
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
		{
			result[i][j] = 0;
			for (size_t k = 0; k < N; ++k)
				result[i][j] += matrix[i][k] * other.matrix[k][j];
		}
	return result;
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator*=(double k)
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] *= k;
	if (!isnan(determinant))
		determinant *= pow(k, N);
	return *this;
}

template<std::size_t N>
SquareMatrix<N>& SquareMatrix<N>::operator/=(double k)
{
	for (size_t i = 0; i < N; ++i)
		for (size_t j = 0; j < N; ++j)
			matrix[i][j] /= k;
	if (!isnan(determinant))
		determinant /= pow(k, N);
	return *this;
}

template<std::size_t N>
SquareMatrix<N> SquareMatrix<N>::operator/(double d) const
{
	SquareMatrix result = *this;
	result /= d;
	return result;
}

template<std::size_t N>
ColumnMatrix<N> SquareMatrix<N>::operator*(const ColumnMatrix<N>& k)
{
	ColumnMatrix<N> result;
	for (std::size_t i = 0; i < N; ++i)
	{
		result[i] = 0;
		for (std::size_t j = 0; j < N; ++j)
			result[i] += matrix[i][j] * k[j];
	}
	return result;
}

template<std::size_t N>
SquareMatrix<N> operator*(double k, const SquareMatrix<N>& m)
{
	SquareMatrix<N> result = m;
	result *= k;
	return result;
}

template<std::size_t N>
SquareMatrix<N> operator*(const SquareMatrix<N>& m, double k)
{
	return k*m;
}

template<std::size_t N>
double* SquareMatrix<N>::operator[](std::size_t i)
{
	resetDeterminant();
	return matrix[i];
}

template<std::size_t N>
double SquareMatrix<N>::operator[](std::size_t i) const
{
	return matrix[i];
}

template<std::size_t N>
std::ostream& operator<<(std::ostream& s, const SquareMatrix<N>& m)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
			s << m.matrix[i][j] << '\t';
		s << std::endl;
	}
	return s;
}

template<std::size_t N>
std::istream& operator>>(std::istream& s, SquareMatrix<N>& m)
{
	for (std::size_t i = 0; i < N; ++i)
		for (std::size_t j = 0; j < N; ++j)
			s >> m.matrix[i][j];
	m.resetDeterminant();
	return s;
}

template<std::size_t N>
SquareMatrix<N - 1> smaller(const SquareMatrix<N>& m, std::size_t deleted_row, std::size_t deleted_col)
{
	SquareMatrix<N - 1> result;
	for (std::size_t i = 0; i < deleted_row; ++i)
	{
		for (std::size_t j = 0; j < deleted_col; ++j)
			result.matrix[i][j] = m.matrix[i][j];
		for (std::size_t j = deleted_col + 1; j < N; ++j)
			result.matrix[i][j-1] = m.matrix[i][j];
	}
	for (std::size_t i = deleted_row + 1; i < N; ++i)
	{
		for (std::size_t j = 0; j < deleted_col; ++j)
			result.matrix[i-1][j] = m.matrix[i][j];
		for (std::size_t j = deleted_col + 1; j < N; ++j)
			result.matrix[i-1][j-1] = m.matrix[i][j];
	}
	return result;
}

template<std::size_t N>
double det(const SquareMatrix<N>& m)
{
	if (std::isnan(m.determinant))
	{
		double result = 0;
		std::size_t row = 0;
		for (std::size_t i = 0; i < N; ++i)
			result += m.matrix[row][i] * det(smaller(m, row, i)) * ( (row + i) % 2 == 0 ? 1: -1 );
		m.determinant = result;
	}
	return m.determinant;
}

template<std::size_t N=2>
double det(const SquareMatrix<2>& m)
{
	if (std::isnan(m.determinant))
		m.determinant = m.matrix[0][0] * m.matrix[1][1] - m.matrix[1][0] * m.matrix[0][1];
	return m.determinant;
}

template<std::size_t N = 1>
double det(const SquareMatrix<1>& m)
{
	if (std::isnan(m.determinant))
		m.determinant = m.matrix[0][0];
	return m.determinant;
}

template<std::size_t N>
SquareMatrix<N> transponse(const SquareMatrix<N>& m)
{
	SquareMatrix<N> result;
	for (std::size_t i = 0; i < N; ++i)
		for (std::size_t j = 0; j < N; ++j)
			result.matrix[i][j] = m.matrix[j][i];
	result.determinant = m.determinant;
	return result;
}

template<std::size_t N>
SquareMatrix<N> invertible(const SquareMatrix<N>& m)
{
	SquareMatrix<N> res;

	double* minors = nullptr;
	if (std::isnan(m.determinant))
		minors = new double[N];
	for (std::size_t row = 0; row < N; ++row)
		for (std::size_t col = 0; col < N; ++col)
		{
			res.matrix[row][col] = det(smaller(m, row, col)) * ((row + col) % 2 == 0 ? 1 : -1);
			if (row == 0 && std::isnan(m.determinant))
				minors[col] = res.matrix[row][col];
		}

	if (std::isnan(m.determinant))
	{
		double determinant = 0;
		std::size_t row = 0;
		for (std::size_t i = 0; i < N; ++i)
			determinant += m.matrix[row][i] * minors[i];
		delete[] minors;
		m.determinant = determinant;
	}

	res /= m.determinant;
	res.determinant = 1 / m.determinant;
	return transponse(res);
}

template<std::size_t N=1>
SquareMatrix<1> invertible(const SquareMatrix<1>& m)
{
	SquareMatrix<1> res;
	res.matrix[0][0] = 1 / m.matrix[0][0];
	res.determinant = res.matrix[0][0];
	return transponse(res);
}
