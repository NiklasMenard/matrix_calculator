/**
 \file compositeelement.hpp
 \brief Header for CompositeElement class
 */
#ifndef COMPOSITEELEMENT_H_INCLUDED
#define COMPOSITEELEMENT_H_INCLUDED
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include "valuation.hpp"
#include "element.hpp"

/**
 \class CompositeElement
 \brief A class for CompositeElement
 */
class CompositeElement : public Element{

private:

	std::unique_ptr<Element> oprnd1;
	std::unique_ptr<Element> oprnd2;
	std::function<int(int,int)> op_fun;
	char op_ch;

public:

	/**
	 \brief Default constructor
	 */
	CompositeElement();

	/**
	 \brief Parametric constructor
	 \param const Element&, const Element&, const std::function<int(int,int, )>, char
	 */
	CompositeElement(const Element&, const Element&, const std::function<int(int,int)>& , char);

	/**
	 \brief Parametric constructor
	 \param const CompositeElement&
	 */
	CompositeElement(const CompositeElement&);

	/**
	 \brief Operator to equal CompositeElement values
	 \param CompositeElement
	 \return this CompositeElement
	 */
	CompositeElement& operator=(const CompositeElement&);

	/**
	 \brief Destructor
	 */
	virtual ~CompositeElement() = default;

	/**
	 \brief clone function
	 */
	std::unique_ptr<Element> clone() const override;

	/**
	 \brief Makes a string representation of CompositeElement
	 \return The string representation
	 */
	std::string toString() const;

	/**
	 \brief evaluate function
	 */
	int evaluate(const Valuation&) const override;

};

std::ostream& operator<<(std::ostream& os, const CompositeElement& ie);

#endif
