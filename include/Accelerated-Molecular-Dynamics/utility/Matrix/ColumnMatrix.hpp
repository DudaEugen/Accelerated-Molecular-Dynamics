#pragma once
#ifndef TAHD_COLUMN_MATRIX_H
#define TAHD_COLUMN_MATRIX_H

#include <utility>
#include <initializer_list>
#include <iostream>

template<std::size_t N>
class ColumnMatrix;

template<std::size_t N>
std::ostream& operator<<(std::ostream& s, const ColumnMatrix<N>& m);
template<std::size_t N>
std::istream& operator>>(std::istream& s, ColumnMatrix<N>& m);

template<std::size_t N>
class ColumnMatrix
{
	double* col;

	void destroy() noexcept;
public:
	ColumnMatrix();
	ColumnMatrix(const ColumnMatrix& other);
	ColumnMatrix(ColumnMatrix&& other) noexcept;
	ColumnMatrix& operator=(ColumnMatrix&& other) noexcept;
	~ColumnMatrix();

	ColumnMatrix(const std::initializer_list<double>& init_list);
	ColumnMatrix& operator=(const ColumnMatrix& other) noexcept;
	double& operator[](std::size_t index);
	double& operator[](std::size_t index) const;

	template<std::size_t U>
	friend std::ostream& operator<<(std::ostream& s, const ColumnMatrix<U>& c);
	template<std::size_t U>
	friend std::istream& operator>>(std::istream& s, ColumnMatrix<U>& c);
};

template<std::size_t N>
void ColumnMatrix<N>::destroy() noexcept
{
	if (col != nullptr)
		delete[] col;
}

template<std::size_t N>
ColumnMatrix<N>::ColumnMatrix()
{
	col = new double [N];
}

template<std::size_t N>
ColumnMatrix<N>::ColumnMatrix(const ColumnMatrix& other)
: ColumnMatrix()
{
	*this = other;
}

template<std::size_t N>
ColumnMatrix<N>::ColumnMatrix(ColumnMatrix&& other) noexcept
{
	*this = std::move(other);
}

template<std::size_t N>
ColumnMatrix<N>& ColumnMatrix<N>::operator=(ColumnMatrix&& other) noexcept
{
	col = other.col;
	other.col = nullptr;
	return *this;
}

template<std::size_t N>
ColumnMatrix<N>::~ColumnMatrix()
{
	destroy();
}

template<std::size_t N>
ColumnMatrix<N>::ColumnMatrix(const std::initializer_list<double>& init_list)
: ColumnMatrix()
{
	for (size_t i = 0; i < N; ++i)
		col[i] = *(init_list.begin() + i);
}

template<std::size_t N>
ColumnMatrix<N>& ColumnMatrix<N>::operator=(const ColumnMatrix& other) noexcept
{
	for (size_t i = 0; i < N; ++i)
		col[i] = other.col[i];
	return *this;
}

template<std::size_t N>
double& ColumnMatrix<N>::operator[](std::size_t index)
{
	return col[index];
}

template<std::size_t N>
double& ColumnMatrix<N>::operator[](std::size_t index) const
{
	return col[index];
}

template<std::size_t N>
std::ostream& operator<<(std::ostream& s, const ColumnMatrix<N>& c)
{
	for (std::size_t i = 0; i < N; ++i)
		s << c.col[i] << std::endl;
	return s;
}

template<std::size_t N>
std::istream& operator>>(std::istream& s, ColumnMatrix<N>& c)
{
	for (std::size_t i = 0; i < N; ++i)
		s >> c.col[i];
	return s;
}

#endif	//TAHD_COLUMN_MATRIX_H
