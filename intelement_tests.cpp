/**
 \file intelement_tests.cpp
 \brief tests for Intelement class
 */
//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "squarematrix.hpp"
#include "intelement.hpp"
#include <iostream>

TEST_CASE("Intelement tests") {

	IntElement test1 { 1 };
	IntElement test2 { 7 };
	IntElement test3 { 2 };

	//test clone function
	std::unique_ptr<IntElement> testclone;
	testclone = test2.clone();
	CHECK(*testclone == test2);

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

	test1 = test2;
	CHECK(test1==test2);

}
