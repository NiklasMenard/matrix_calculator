#include "catch.hpp"
#include "valuation.hpp"
#include "intelement.hpp"
#include <sstream>

TEST_CASE("Intelement tests") {

	IntElement test1 { 1 };
	IntElement test2 { 7 };
	IntElement test3 { 2 };

	//test clone function
	std::unique_ptr<Element> testclone;
	testclone = test2.clone();
	CHECK(testclone.get()->toString() == test2.toString());

	//check testval and +, - and * operators
	CHECK(test1.getVal() == 1);
	test1 = test1 + test2;
	CHECK(test1.getVal() == 8);
	test1 = test1 - test2;
	CHECK(test1.getVal() == 1);
	test1 = test1 * test3;
	CHECK(test1.getVal() == 2);
	CHECK(test1.toString() == "2");

	//test stringstream
	std::stringstream str;
	str << test1;
	CHECK(str.str() == "2");

	test1.setVal(10);
	CHECK(test1.getVal() == 10);

	//test empty constructor
	IntElement test4 { };
	CHECK(test4.getVal() == 0);

	//test = operator
	test2 = test1;
	CHECK(test2.toString() == "10");
	test2 = test1;
	CHECK(test2.toString() == "10");

	//test == operator
	test1 = test2;
	CHECK(test1 == test2);

	Valuation ievalues;
	ievalues.insert(std::pair<char, int>('a', 0));
	CHECK(test1.evaluate(ievalues) == 10);

}

