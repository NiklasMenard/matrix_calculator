/**
 \file intelement.cpp
 \brief Code for VariableElement class
 */
#include <sstream>
#include <iostream>
#include "varelement.hpp"

VariableElement::VariableElement() :
		val() {
}

VariableElement::VariableElement(char v) :
		val { v } {
}

char VariableElement::getVal(){

	return val;
}

void VariableElement::setVal(char val) {
	this->val = val;
}

int VariableElement::evaluate(const Valuation& valuation) const {

	int value = 0;
	if ( valuation.find(val) == valuation.end() ) {
		throw std::invalid_argument("Value not found");
	} else {
	  value = valuation.at(val);
	}

	return value;

}

std::unique_ptr<Element> VariableElement::clone() const {

	return std::unique_ptr<Element>(new VariableElement(*this));

}

std::string VariableElement::toString() const {
	std::stringstream strm;
	strm << val;
	return strm.str();
}

std::ostream& operator<<(std::ostream& os, const VariableElement& ie) {
	os << ie.toString();
	return os;
}

