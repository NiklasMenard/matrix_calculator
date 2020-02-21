#include "catch.hpp"
#include "valuation.hpp"
#include "varelement.hpp"
#include "symbolicmatrix.hpp"
#include "compositeelement.hpp"


TEST_CASE("CompositeElement tests") {

	Valuation values;
	values.insert(std::pair<char, int>('a', 1));
	values.insert(std::pair<char, int>('b', 2));

	VariableElement ve('a');
	IntElement ie(1);

	//Testing constructors
	CompositeElement ce1(ve,ie,std::plus<int>(), '+');
	CHECK(ce1.toString()=="(a+1)");

	CompositeElement ce2(ce1);
	CHECK(ce2.toString()=="(a+1)");

	//Test clone
	std::unique_ptr<Element> testclone;
	testclone = ce2.clone();
	CHECK(testclone->toString() == "(a+1)");

	//test stringstream
	std::stringstream str;
	str << ce2;
	CHECK(str.str() == "(a+1)");

	//test move
	ce1 = std::move(ce2);
	CHECK(ce1.toString()=="(a+1)");
}

