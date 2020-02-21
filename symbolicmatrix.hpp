/**
 \file SymbolicSquareMatrix.hpp
 \brief Header for SquareMatrix class
 */
#ifndef SYMBOLICMATRIX_H_INCLUDED
#define SYMBOLICMATRIX_H_INCLUDED
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "element.hpp"
#include "concretematrix.hpp"


/**
 \class SymbolicSquareMatrix
 \brief A class for square matrix
 */
class SymbolicSquareMatrix {

private:

	unsigned int n;
	std::vector<std::vector<std::unique_ptr<Element>>> elements;

public:

	/**
	 \brief Default constructor
	 */
	SymbolicSquareMatrix();

	/**
	 \brief Parametric constructor
	 \string parameter
	 */
	SymbolicSquareMatrix(const std::string&);

	/**
	 \brief Parametric constructor
	 \SymbolicSquareMatrix parameter
	 */
	SymbolicSquareMatrix(const SymbolicSquareMatrix& SquareMatrix);

	/**
	 \brief Move constructor
	 */
	SymbolicSquareMatrix(SymbolicSquareMatrix&&);

	/**
	 \brief Destructor
	 */
	virtual ~SymbolicSquareMatrix() = default;

	/**
	 \brief Function to transpose squarematrix
	 */
	SymbolicSquareMatrix transpose();

	/**
	 \brief Function to check if string is SymbolicSquareMatrix
	 \if string is SymbolicSquareMatrix then it sets it into
	 \elements vector
	 \param SymbolicSquareMatrix in string form
	 \return bool
	 */
	bool isSquareMatrix(const std::string&);

	/**
	 \brief Operator for SymbolicSquareMatrix equal sign
	 \param squarematrix to equal with
	 \return equal squarematrix
	 */
	SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix&);

	/**
	 \brief Move Operator for squarematrix equal sign
	 param SymbolicSquareMatrix to move values from
	 return SymbolicSquareMatrix
	 */
	SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&&);

	/**
	 \brief Operator compare SymbolicSquareMatrix values
	 \param SquareMatrix
	 \return boolean
	 */
	bool operator==(const SymbolicSquareMatrix&) const;

	/**
	 \brief print function
	 \param os stream
	 */
	void print(std::ostream& os) const;

	/**
	 \brief Makes a string representation of SymbolicSquareMatrix
	 \return The string representation
	 */
	std::string toString() const;

	ConcreteSquareMatrix evaluate(const Valuation&);

	/**
	 \brief Operator for SymbolicSquareMatrix addition
	 \param squarematrix to add with
	 \return the sum of SymbolicSquareMatrix
	 */
	SymbolicSquareMatrix operator+(const SymbolicSquareMatrix&);

	/**
	 \brief Operator for SymbolicSquareMatrix subtraction
	 \param squarematrix to subtract with
	 \return the subtraction of SymbolicSquareMatrix
	 */
	SymbolicSquareMatrix operator-(const SymbolicSquareMatrix&);

	/**
	 \brief Operator for SymbolicSquareMatrix multiplication
	 \param squarematrix to multiply with
	 \return The product of SymbolicSquareMatrix
	 */
	SymbolicSquareMatrix operator*(const SymbolicSquareMatrix&);

};


/**
 \brief Output operator
 \param os stream to print in
 \param SymbolicSquareMatrix ref to a SymbolicSquareMatrix object
 */
std::ostream& operator<<(std::ostream&, const SymbolicSquareMatrix&);


#endif
