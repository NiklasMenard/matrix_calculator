#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "valuation.hpp"
#include <memory>


/**
 \class Element
 \brief A class for Element
 */
class Element {

public:

	/**
	 \brief Virtual clone function
	 */
	virtual std::unique_ptr<Element> clone() const = 0;
	/**
	 \brief Virtual toString function
	 */
	virtual std::string toString() const = 0;
	/**
	 \brief Virtual evaluate function
	 */
	virtual int evaluate(const Valuation&) const = 0;
	/**
	 \brief Default constructor
	 */
	virtual ~Element()=default;

};
/**
 \brief << Operator overload
 */
std::ostream& operator<<(std::ostream&, const Element&);

bool operator==(const Element&, const Element&);

#endif
