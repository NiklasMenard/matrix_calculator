/**
 \file squarematrix.cpp
 \brief code for Squarematrix class
 */
#include "squarematrix.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>

SquareMatrix::SquareMatrix() {

	this->n = 0;
}

SquareMatrix::SquareMatrix(const std::string &str) {

	if (isSquareMatrix(str) == false) {
		throw std::invalid_argument("Invalid matrix");
	}

}

SquareMatrix::SquareMatrix(const SquareMatrix& m) {

	if (isSquareMatrix(m.toString()) == false) {
		throw std::invalid_argument("Invalid matrix");
	} else {

		this->n = m.n;
		for (unsigned int i = 0; i < m.elements.size(); i++) {
			for (unsigned int j = 0; j < m.elements[i].size(); j++) {
				*elements[i][j] = *m.elements[i][j].get()->clone();
			}
		}
	}
}

SquareMatrix::SquareMatrix(SquareMatrix&& m) {

	n = std::move(m.n);
	elements = std::move(m.elements);

}

int SquareMatrix::getN() const {
	return this->n;
}

bool SquareMatrix::isSquareMatrix(const std::string &str) {

	std::stringstream input(str);
	char c;
	int number;

	int rows = 0;
	int columns = 0;
	int temp_columns = 0;
	std::vector<std::unique_ptr<IntElement>> row_elements;
	std::string tail;

	input >> c;
	if (!input.good() || c != '[') {
		return false;
	}

	input >> c;
	while (!input.good() || c != ']') {
		if (!input.good() || c != '[')
			return false;
		do {
			input >> number;
			if (!input.good()) {
				return false;
			}
			row_elements.push_back(
					std::unique_ptr<IntElement>(new IntElement(number)));

			temp_columns++;
			input >> c;
			if (!input.good() || (c != ',' && c != ']')) {
				return false;
			}
		} while (c != ']');

		elements.push_back(std::move(row_elements));
		row_elements.clear();

		if (columns == 0) {
			columns = temp_columns;
		}
		if (temp_columns != columns) {
			return false;
		}

		temp_columns = 0;
		rows++;
		input >> c;

		if (input.eof()) {
			return false;
		}

	}

	input >> tail;
	if (tail != "") {
		return false;
	}

	if (rows == columns) {
		this->n = columns;
		return true;
	} else {
		return false;
	}
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& m) {

	if (n != m.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			*elements[i][j] = *elements[i][j] + *m.elements[i][j];
		}
	}

	return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& m) {

	if (n != m.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			*elements[i][j] = *elements[i][j] - *m.elements[i][j];
		}
	}
	return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& m) {

	if (n != m.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	SquareMatrix empty_temp(m);
	empty_temp -= m;
	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			for (unsigned int k = 0; k < elements.size(); k++) {
				*empty_temp.elements[i][j] += *elements[i][k]
						* *m.elements[k][j];
			}
		}
	}

	*this = empty_temp;

	return *this;
}

SquareMatrix SquareMatrix::transpose() {

	SquareMatrix temp_matrix(*this);

	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			*elements[i][j] = *temp_matrix.elements[j][i];
		}
	}

	return *this;
}

bool SquareMatrix::operator==(const SquareMatrix& m) const {
	return toString() == m.toString();
}

SquareMatrix& SquareMatrix::operator=(const SquareMatrix& m) {

	if (this == &m) {
		return *this;
	}

	SquareMatrix temp_copy(m);
	std::swap(elements, temp_copy.elements);
	std::swap(n, temp_copy.n);

	return *this;
}

SquareMatrix& SquareMatrix::operator=(SquareMatrix&& m) {

	if (this == &m)
		return *this;

	n = std::move(m.n);
	elements = std::move(m.elements);

	return *this;
}

SquareMatrix operator+(const SquareMatrix& first, const SquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	SquareMatrix matrix_temp(first);
	matrix_temp += second;
	return matrix_temp;

}

SquareMatrix operator-(const SquareMatrix& first, const SquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	SquareMatrix matrix_temp(first);
	matrix_temp -= second;
	return matrix_temp;

}

SquareMatrix operator*(const SquareMatrix& first, const SquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	SquareMatrix matrix_temp(first);
	matrix_temp *= second;
	return matrix_temp;

}

void SquareMatrix::print(std::ostream& os) const {
	os << toString();
}

std::string SquareMatrix::toString() const {

	std::stringstream strm;
	strm << "[";
	for (unsigned int i = 0; i < elements.size(); i++) {
		strm << "[";
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			if (j != unsigned(n) - 1) {
				strm << *elements[i][j] << ",";
			} else {
				strm << *elements[i][j];
			}
		}
		strm << "]";
	}
	strm << "]";
	return strm.str();
}

std::ostream& operator<<(std::ostream& os, const SquareMatrix& m) {
	os << m.toString();
	return os;
}
