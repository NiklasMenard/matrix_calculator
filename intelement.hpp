/**
 \file intelement.hpp
 \brief Header for IntElement class
 */
#ifndef INTELEMENT_H_INCLUDED
#define INTELEMENT_H_INCLUDED
#include <ostream>
#include <string>
#include <memory>
/**
 \class IntElement
 \brief A class for intelement
 */
class IntElement {

private:

	int value;

public:

	/**
	 \brief Default constructor
	 */
	IntElement();

	/**
	 \brief Parametric constructor
	 \param intelement value
	 */
	IntElement(int);

	/**
	 \brief Parametric constructor
	 \param intelement object
	 */
	IntElement(const IntElement&);

	/**
	 \brief Destructor
	 */
	virtual ~IntElement() = default;
	/**
	 \brief Getter of intelement value
	 \return the value
	 */
	int getVal() const;
	/**
	 \brief setter of intelement value
	 \set value
	 */
	void setVal(int);

	/**
	 \brief Operator to equal intelement values
	 \param intelement
	 \return this intelement
	 */
	IntElement& operator=(const IntElement&);

	/**
	 \brief Operator to sum intelement values
	 \param intelement
	 \return sum of value
	 */
	IntElement& operator+=(const IntElement&);
	/**
	 \brief Operator to subtract intelement values
	 \param intelement
	 \return subtraction of value
	 */
	IntElement& operator-=(const IntElement&);
	/**
	 \brief Operator to multiply intelement values
	 \param intelement
	 \return multiplication of values
	 */
	IntElement& operator*=(const IntElement&);

	/**
	 \brief Operator compare intelement values
	 \param intelement
	 \return boolean
	 */
	bool operator==(const IntElement&) const;

	/**
	 \brief Makes a string representation of Intelelement
	 \return The string representation
	 */
	std::string toString() const;

	/**
	 \brief clone function
	 */
	std::unique_ptr<IntElement> clone() const;

};

/**
 \brief Operator to multiply intelement values
 \param intelement1
 \param intelement2
 \return intelement Object with multiplied value
 */
IntElement operator*(const IntElement&, const IntElement&);

/**
 \brief Operator to sum intelement values
 \param intelement1
 \param intelement2
 \return intelement Object with summed value
 */
IntElement operator+(const IntElement&, const IntElement&);

/**
 \brief Operator to subtract intelement values
 \param intelement1
 \param intelement2
 \return intelement Object with subtracted value
 */
IntElement operator-(const IntElement&, const IntElement&);

/**
 \brief Output operator
 \param os stream to print in
 \param intelement ref to a intelement object
 */
std::ostream& operator<<(std::ostream& os, const IntElement& ie);

#endif // INTELEMENT_H_INCLUDED
