/**
 \file squarematrix.hpp
 \brief Header for SquareMatrix class
 */
#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "intelement.hpp"

/**
 \class squarematrix
 \brief A class for square matrix
 */
class SquareMatrix {

private:

	int n;
	std::vector<std::vector<std::unique_ptr<IntElement>>> elements;

public:

	/**
	 \brief Default constructor
	 */
	SquareMatrix();

	/**
	 \brief Parametric constructor
	 \string parameter
	 */
	SquareMatrix(const std::string&);

	/**
	 \brief Parametric constructor
	 \squarematrix parameter
	 */
	SquareMatrix(const SquareMatrix& SquareMatrix);

	/**
	 \brief Move constructor
	 */
	SquareMatrix(SquareMatrix&&);

	/**
	 \brief Destructor
	 */
	virtual ~SquareMatrix() = default;

	/**
	 \brief getter for N value
	 */
	int getN() const;

	/**
	 \brief Function to transpose squarematrix
	 */
	SquareMatrix transpose();

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

	SquareMatrix& operator+=(const SquareMatrix&);

	/**
	 \brief Operator for squarematrix subtraction
	 \param squarematrix to subtract with
	 \return the subtraction of squarematrixes
	 */
	SquareMatrix& operator-=(const SquareMatrix&);

	/**
	 \brief Operator for squarematrix multiplication
	 \param squarematrix to multiply with
	 \return The product of squarematrixes
	 */
	SquareMatrix& operator*=(const SquareMatrix&);

	/**
	 \brief Operator for squarematrix equal sign
	 \param squarematrix to equal with
	 \return equal squarematrix
	 */
	SquareMatrix& operator=(const SquareMatrix&);

	/**
	 \brief Move Operator for squarematrix equal sign
	 param squarematrix to move values from
	 return squarematrix
	 */
	SquareMatrix& operator=(SquareMatrix&&);

	/**
	 \brief Operator compare SquareMatrix values
	 \param SquareMatrix
	 \return boolean
	 */
	bool operator==(const SquareMatrix&) const;

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
std::ostream& operator<<(std::ostream&, const SquareMatrix&);

/**
 \brief Operator to sum SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with summed value
 */
SquareMatrix operator+(const SquareMatrix&, const SquareMatrix&);

/**
 \brief Operator to subtract SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with subtracted value
 */
SquareMatrix operator-(const SquareMatrix&, const SquareMatrix&);

/**
 \brief Operator to multiply SquareMatrix values
 \param SquareMatrix
 \param SquareMatrix
 \return SquareMatrix Object with multiplied value
 */
SquareMatrix operator*(const SquareMatrix&, const SquareMatrix&);

#endif// SQUAREMATRIX_H_INCLUDED
