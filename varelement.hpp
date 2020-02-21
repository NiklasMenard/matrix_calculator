/**
 \file intelement.hpp
 \brief Header for IntElement class
 */
#ifndef VARELEMENT_H_INCLUDED
#define VARELEMENT_H_INCLUDED
#include <ostream>
#include <string>
#include <memory>
#include "valuation.hpp"
#include "element.hpp"
/**
 \class IntElement
 \brief A class for intelement
 */
class VariableElement : public Element{

private:

	char val;

public:

	/**
	 \brief Default constructor
	 */
	VariableElement();

	/**
	 \brief Parametric constructor
	 \param intelement value
	 */
	VariableElement(char);

	/**
	 \brief Destructor
	 */
	virtual ~VariableElement() = default;
	/**
	 \brief Getter of intelement value
	 \return the value
	 */
	char getVal();
	/**
	 \brief setter of intelement value
	 \set value
	 */
	void setVal(char);

	/**
	 \brief Makes a string representation of Intelelement
	 \return The string representation
	 */
	std::string toString() const;

	/**
	 \brief clone function
	 */
	std::unique_ptr<Element> clone() const override;

	/**
	 \brief evaluate function
	 */
	int evaluate(const Valuation&) const override;

};

std::ostream& operator<<(std::ostream& os, const VariableElement& ie);

#endif
