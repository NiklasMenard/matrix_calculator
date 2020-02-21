/**
 \file symbolicmatrix.cpp
 \brief code for SymbolicSquareMatrix class
 */
#include "symbolicmatrix.hpp"
#include "varelement.hpp"
#include "intelement.hpp"
#include "compositeelement.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>

SymbolicSquareMatrix::SymbolicSquareMatrix() :elements{}  {

	this->n = 0;
}

SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string &str) {

	if (isSquareMatrix(str) == false) {
		throw std::invalid_argument("Invalid matrix");
	}

}

SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& sm) {

	this->n = sm.n;
	isSquareMatrix(sm.toString());
}

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& sm) {

	n = std::move(sm.n);
	elements = std::move(sm.elements);

}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(
		const SymbolicSquareMatrix& sm) {

	if (this == &sm) return *this;

	SymbolicSquareMatrix temp_copy(sm);
	std::swap(elements, temp_copy.elements);
	std::swap(n, temp_copy.n);

	return *this;
}

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(
		SymbolicSquareMatrix&& sm) {

	if (this == &sm) return *this;

	n = std::move(sm.n);
	elements = std::move(sm.elements);

	return *this;
}

bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& sm) const {
	return toString() == sm.toString();
}

bool SymbolicSquareMatrix::isSquareMatrix(const std::string &str) {

	std::stringstream input(str);
	char c;
	int number;

	int rows = 0;
	int columns = 0;
	int temp_columns = 0;
	std::vector<std::unique_ptr<Element>> row_elements;
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
            char character;
            character = input.peek();
            if(isalpha(character)) {
                input >> c;
                row_elements.push_back(std::move(std::unique_ptr<Element>(new VariableElement(c))));
            } else {
                input >> number;
                if (input.fail()) {
                    return false;
                }
                row_elements.push_back(std::move(std::unique_ptr<IntElement>(new IntElement(number))));
            }

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

SymbolicSquareMatrix SymbolicSquareMatrix::transpose() {

	SymbolicSquareMatrix temp_matrix(*this);

	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			elements[i][j].swap(temp_matrix.elements[j][i]);
		}
	}

	return *this;
}

ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& val) {

	ConcreteSquareMatrix cm;

	for (unsigned int i = 0; i < elements.size(); i++) {
		cm.elements.push_back({});
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			cm.elements.back().push_back(std::unique_ptr<IntElement>(new IntElement(elements[i][j]->evaluate(val))));
		}
	}

	return cm;
}

void SymbolicSquareMatrix::print(std::ostream& os) const {
	os << toString();
}

std::string SymbolicSquareMatrix::toString() const {

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


SymbolicSquareMatrix SymbolicSquareMatrix::operator+ (const SymbolicSquareMatrix& sm) {

	if (n != sm.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	SymbolicSquareMatrix temp_matrix(sm);
	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			temp_matrix.elements[i][j] = std::unique_ptr<Element>(new CompositeElement (*elements[i][j], *sm.elements[i][j], std::plus<int>(), '+'));
		}
	}

	return temp_matrix;
}

SymbolicSquareMatrix SymbolicSquareMatrix::operator- (const SymbolicSquareMatrix& sm) {

	if (n != sm.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	SymbolicSquareMatrix temp_matrix(sm);
	for (unsigned int i = 0; i < elements.size(); i++) {
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			temp_matrix.elements[i][j] = std::unique_ptr<Element>(new CompositeElement (*elements[i][j], *sm.elements[i][j], std::minus<int>(), '-'));
		}
	}

	return temp_matrix;

}

SymbolicSquareMatrix SymbolicSquareMatrix::operator* (const SymbolicSquareMatrix& sm) {

	if (n != sm.n) {
		throw std::invalid_argument("Error: different size matrices");
	}

	SymbolicSquareMatrix temp_matrix;
	std::unique_ptr<Element> temp;
	for (unsigned int i = 0; i < elements.size(); i++) {
		temp_matrix.elements.push_back({});
		for (unsigned int j = 0; j < elements[i].size(); j++) {
			temp_matrix.elements.back().push_back(std::unique_ptr<Element>(new IntElement(0)));
			for (unsigned int k = 0; k < elements.size(); k++) {
				temp = std::unique_ptr<Element>(new CompositeElement (*elements[i][k], *sm.elements[k][j], std::multiplies<int>(), '*'));
				temp_matrix.elements[i][j] = std::unique_ptr<Element>(new CompositeElement (*temp_matrix.elements[i][j], *temp, std::plus<int>(), '+'));
			}
		}
	}

	return temp_matrix;
}

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m) {
	os << m.toString();
	return os;
}
