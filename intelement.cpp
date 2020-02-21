/**
 \file intelement.cpp
 \brief Code for IntElement class
 */
#include <sstream>
#include "intelement.hpp"

IntElement::IntElement() :
		value(0) {
}

IntElement::IntElement(int v) :
		value { v } {
}

IntElement::IntElement(const IntElement& ie) {
	this->value = ie.value;
}

int IntElement::getVal() const {
	return this->value;
}

void IntElement::setVal(int val) {
	this->value = val;
}

int IntElement::evaluate(const Valuation& valuation) const {

	return value;
}

IntElement& IntElement::operator=(const IntElement& ie) {
	this->value = ie.value;
	return *this;
}

IntElement& IntElement::operator*=(const IntElement& i) {

	this->value = value * i.value;
	return *this;
}

IntElement& IntElement::operator+=(const IntElement& i) {

	this->value = value + i.value;
	return *this;
}

IntElement& IntElement::operator-=(const IntElement& i) {

	this->value = value - i.value;
	return *this;
}

std::unique_ptr<Element> IntElement::clone() const {

	return std::unique_ptr<Element>(new IntElement(*this));

}


IntElement operator*(const IntElement&first, const IntElement&second) {
	IntElement ie_temp(first);
	ie_temp *= second;
	return ie_temp;
}

IntElement operator+(const IntElement&first, const IntElement&second) {
	IntElement ie_temp(first);
	ie_temp += second;
	return ie_temp;
}

IntElement operator-(const IntElement&first, const IntElement&second) {
	IntElement ie_temp(first);
	ie_temp -= second;
	return ie_temp;

}

std::string IntElement::toString() const {
	std::stringstream strm;
	strm << value;
	return strm.str();
}

std::ostream& operator<<(std::ostream& os, const IntElement& ie) {
	os << ie.toString();
	return os;
}

