/**
    \file squarematrix_tests.cpp
    \brief tests for Squarematrix class
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "squarematrix.hpp"
#include "intelement.hpp"
#include <iostream>

TEST_CASE("Squarematrix tests") {

	SquareMatrix sqtest1("[[1,2][3,4]]");
	CHECK(sqtest1.toString() == "[[1,2][3,4]]");

	SquareMatrix sqtest2(sqtest1);
	CHECK(sqtest2.toString() == "[[1,2][3,4]]");

	sqtest1 = sqtest1 + sqtest2;
	CHECK(sqtest1.toString() == "[[2,4][6,8]]");
	sqtest1 = sqtest1 - sqtest2;
	CHECK(sqtest1.toString() == "[[1,2][3,4]]");
	sqtest1 = sqtest1 * sqtest2;
	CHECK(sqtest1.toString() == "[[7,10][15,22]]");

	SquareMatrix sqtest3 {};
	CHECK(sqtest3.toString() == "[]");

	sqtest2 = sqtest1;
	CHECK(sqtest2.toString() == "[[7,10][15,22]]");

	std::stringstream str;
	str << sqtest1;
	CHECK(str.str() == "[[7,10][15,22]]");

	std::ostringstream output_buffer;
	sqtest1.print(output_buffer);
	CHECK(output_buffer.str() == "[[7,10][15,22]]");

	SquareMatrix sqtest5("[[7,10][15,22]]");
	CHECK_NOTHROW(sqtest5);

	CHECK(sqtest1 == sqtest5);

	sqtest5.transpose();
	CHECK(sqtest5.toString() == "[[7,15][10,22]]");

	SquareMatrix move = std::move(sqtest5);
	CHECK(move.toString() == "[[7,15][10,22]]");

}


TEST_CASE("Sqmatrix test two","[incorrect]"){

	SquareMatrix sqtest6("[[1,2][3,4]]");
	SquareMatrix sqtest7("[[1,2][5,4]]");
	SquareMatrix sqtest8("[[1,2,4][5,4,4][5,4,4]]");


	CHECK_THROWS(sqtest6 + sqtest8);
	CHECK_THROWS(sqtest6 - sqtest8);
	CHECK_THROWS(sqtest6 * sqtest8);
	CHECK_THROWS_AS(sqtest6* sqtest8, std::domain_error);

	CHECK_FALSE(sqtest6 == sqtest7);

	CHECK_THROWS_AS((SquareMatrix {"[1,77]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {SquareMatrix{"[8,]"}}), std::invalid_argument);
	CHECK_THROWS_WITH((SquareMatrix{"[8,]"}),"Invalid matrix");
	CHECK_THROWS_AS((SquareMatrix {"[[*]]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {" [[1,2][1,2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"asdf"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[a1,a2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1b,2i]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,s]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,,...,,,2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[[1,2,3][1,2,3]]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,2,3][1,2]]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[[1,2][1,2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"(1,2)(1,2)"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,2[1,2]"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[1,2[1,2]''"}), std::invalid_argument);
	CHECK_THROWS_AS((SquareMatrix {"[[1,2][1,2]] f"}), std::invalid_argument);

}
