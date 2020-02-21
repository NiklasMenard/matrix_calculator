/**
 \file compositelement.cpp
 \brief Code for CompositeElement class
 */

#include "compositeelement.hpp"
#include <algorithm>


CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& opc, char op){

	oprnd1 = std::unique_ptr<Element>(e1.clone());
	oprnd2 = std::unique_ptr<Element>(e2.clone());
	op_fun = opc;
	op_ch = op;

}

CompositeElement::CompositeElement(const CompositeElement& ce){

	oprnd1 = std::unique_ptr<Element>(ce.oprnd1->clone());
	oprnd2 = std::unique_ptr<Element>(ce.oprnd2->clone());
	op_ch = ce.op_ch;
	op_fun = ce.op_fun;

}

CompositeElement& CompositeElement::operator=(const CompositeElement& ce){

	if (this == &ce) return *this;

	CompositeElement temp_copy(ce);
	std::swap(oprnd1, temp_copy.oprnd1);
	std::swap(oprnd2, temp_copy.oprnd2);
	std::swap(op_fun, temp_copy.op_fun);
	std::swap(op_ch, temp_copy.op_ch);

	return *this;


}

std::unique_ptr<Element> CompositeElement::clone()const{

	return std::unique_ptr<Element>(new CompositeElement(*this));

}

std::string CompositeElement::toString() const{

	return '(' + oprnd1->toString() + op_ch + oprnd2->toString() + ')';
}

int CompositeElement::evaluate(const Valuation& val) const{

	return op_fun(oprnd1->evaluate(val), oprnd2->evaluate(val));

}

std::ostream& operator<<(std::ostream& os, const CompositeElement& ie) {
	os << ie.toString();
	return os;
}
