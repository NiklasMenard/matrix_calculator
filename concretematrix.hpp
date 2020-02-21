/**
 \file squarematrix.hpp
 \brief Header for SquareMatrix class
 */
#ifndef CONCRETESQUAREMATRIX_H_INCLUDED
#define CONCRETESQUAREMATRIX_H_INCLUDED
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "intelement.hpp"
class SymbolicSquareMatrix;

/**
 \class squarematrix
 \brief A class for square matrix
 */
class ConcreteSquareMatrix {

private:

	friend SymbolicSquareMatrix;
	unsigned int n;
	std::vector<std::vector<std::unique_ptr<IntElement>>> elements;

public:

	/**
	 \brief Default constructor
	 */
	ConcreteSquareMatrix();

	/**
	 \brief Parametric constructor
	 \string parameter
	 */
	ConcreteSquareMatrix(const std::string&);

	/**
	 \brief Parametric constructor
	 \squarematrix parameter
	 */
	ConcreteSquareMatrix(const ConcreteSquareMatrix& SquareMatrix);

	/**
	 \brief Move constructor
	 */
	ConcreteSquareMatrix(ConcreteSquareMatrix&&);

	/**
	 \brief Destructor
	 */
	virtual ~ConcreteSquareMatrix() = default;

	/**
	 \brief getter for N value
	 */
	int getN() const;

	/**
	 \brief Function to transpose squarematrix
	 */
	ConcreteSquareMatrix transpose();

	/**
	 \brief Function to check if string is squarematrix
	 \if string is squarematrix then it sets it into
	 \elements vector
	 \param squarematrix in string form
	 \return bool
	 */
	bool isSquareMatrix(const std::string&);

	/**
	 \brief Operator for squarematrix addition
	 \param squarematrix to add with
	 \return the sum of squarematrixes
	 */

	ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix&);

	/**
	 \brief Operator for squarematrix subtraction
	 \param squarematrix to subtract with
	 \return the subtraction of squarematrixes
	 */
	ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix&);

	/**
	 \brief Operator for squarematrix multiplication
	 \param squarematrix to multiply with
	 \return The product of squarematrixes
	 */
	ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix&);

	/**
	 \brief Operator for squarematrix equal sign
	 \param squarematrix to equal with
	 \return equal squarematrix
	 */
	ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix&);

	/**
	 \brief Move Operator for squarematrix equal sign
	 param squarematrix to move values from
	 return squarematrix
	 */
	ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&&);

	/**
	 \brief Operator compare SquareMatrix values
	 \param SquareMatrix
	 \return boolean
	 */
	bool operator==(const ConcreteSquareMatrix&) const;

	/**
	 \brief print function
	 \param os stream
	 */
	void print(std::ostream& os) const;

	/**
	 \brief Makes a string representation of squarematrix
	 \return The string representation
	 */
	std::string toString() const;

};

/**
 \brief Output operator
 \param os stream to print in
 \param squarematrix ref to a squarematrix object
 */
std::ostream& operator<<(std::ostream&, const ConcreteSquareMatrix&);

/**
 \brief Operator to sum SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with summed value
 */
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&);

/**
 \brief Operator to subtract SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with subtracted value
 */
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&);

/**
 \brief Operator to multiply SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with multiplied value
 */
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&);

#endif
