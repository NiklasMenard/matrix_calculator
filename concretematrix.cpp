/**
 \file squarematrix.cpp
 \brief code for Squarematrix class
 */
#include "concretematrix.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>

ConcreteSquareMatrix::ConcreteSquareMatrix() :
		elements { } {

	this->n = 0;
}

ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string &str) {

	if (isSquareMatrix(str) == false) {
		throw std::invalid_argument("Invalid matrix");
	}

}

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m) {

	this->n = m.n;
	isSquareMatrix(m.toString());
}

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m) {

	n = std::move(m.n);
	elements = std::move(m.elements);

}

int ConcreteSquareMatrix::getN() const {
	return this->n;
}

bool ConcreteSquareMatrix::isSquareMatrix(const std::string &str) {

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

ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(
		const ConcreteSquareMatrix& m) {

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

ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(
		const ConcreteSquareMatrix& m) {

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

ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(
		const ConcreteSquareMatrix& m) {

	if (n != m.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	ConcreteSquareMatrix empty_temp(m);
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

ConcreteSquareMatrix ConcreteSquareMatrix::transpose() {

	ConcreteSquareMatrix temp_matrix(*this);

	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			*elements[i][j] = *temp_matrix.elements[j][i];
		}
	}

	return *this;
}

bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const {
	return toString() == m.toString();
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(
		const ConcreteSquareMatrix& m) {

	if (this == &m) return *this;


	ConcreteSquareMatrix temp_copy(m);
	std::swap(elements, temp_copy.elements);
	std::swap(n, temp_copy.n);

	return *this;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(
		ConcreteSquareMatrix&& m) {

	if (this == &m) return *this;

	n = std::move(m.n);
	elements = std::move(m.elements);

	return *this;
}

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& first,
		const ConcreteSquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	ConcreteSquareMatrix matrix_temp(first);
	matrix_temp += second;
	return matrix_temp;

}

ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& first,
		const ConcreteSquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	ConcreteSquareMatrix matrix_temp(first);
	matrix_temp -= second;
	return matrix_temp;

}

ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& first,
		const ConcreteSquareMatrix& second) {

	if (first.getN() != second.getN()) {
		throw std::domain_error("Error: different size matrices");
	}

	ConcreteSquareMatrix matrix_temp(first);
	matrix_temp *= second;
	return matrix_temp;

}

void ConcreteSquareMatrix::print(std::ostream& os) const {
	os << toString();
}

std::string ConcreteSquareMatrix::toString() const {

	std::stringstream strm;
	strm << "[";
	for (unsigned int i = 0; i < elements.size(); i++) {
		strm << "[";
		bool isfirst = true;
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			if (!isfirst) {
				strm << ",";
			}
			strm << elements[i][j].get()->toString();
			isfirst = false;
		}
		strm << "]";
	}
	strm << "]";
	return strm.str();
}

std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m) {
	os << m.toString();
	return os;
}
