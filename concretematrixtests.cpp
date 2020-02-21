#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "valuation.hpp"
#include "concretematrix.hpp"

TEST_CASE("Concretematrix tests") {

	ConcreteSquareMatrix sqtest1("[[1,2][3,4]]");
	CHECK(sqtest1.toString() == "[[1,2][3,4]]");

	ConcreteSquareMatrix sqtest2(sqtest1);
	CHECK(sqtest2.toString() == "[[1,2][3,4]]");

	//check if is matrix then returns same
	CHECK_NOTHROW(sqtest1 = sqtest1);
	CHECK_NOTHROW(sqtest1 = std::move(sqtest1));


	sqtest1 = sqtest1 + sqtest2;
	CHECK(sqtest1.toString() == "[[2,4][6,8]]");
	sqtest1 = sqtest1 - sqtest2;
	CHECK(sqtest1.toString() == "[[1,2][3,4]]");
	sqtest1 = sqtest1 * sqtest2;
	CHECK(sqtest1.toString() == "[[7,10][15,22]]");
	ConcreteSquareMatrix sqtest3 { };
	CHECK(sqtest3.toString() == "[]");

	sqtest2 = sqtest1;
	CHECK(sqtest2.toString() == "[[7,10][15,22]]");

	std::stringstream str;
	str << sqtest1;
	CHECK(str.str() == "[[7,10][15,22]]");

	std::ostringstream output_buffer;
	sqtest1.print(output_buffer);
	CHECK(output_buffer.str() == "[[7,10][15,22]]");

	ConcreteSquareMatrix sqtest5("[[7,10][15,22]]");
	CHECK_NOTHROW(sqtest5);

	CHECK(sqtest1 == sqtest5);

	sqtest5.transpose();
	CHECK(sqtest5.toString() == "[[7,15][10,22]]");

	ConcreteSquareMatrix move = std::move(sqtest5);
	CHECK(move.toString() == "[[7,15][10,22]]");

}

TEST_CASE("ConcreteSquareMatrix incorrect tests") {

	ConcreteSquareMatrix sqtest6("[[1,2][3,4]]");
	ConcreteSquareMatrix sqtest7("[[1,2][5,4]]");
	ConcreteSquareMatrix sqtest8("[[1,2,4][5,4,4][5,4,4]]");

	CHECK_THROWS(sqtest6 + sqtest8);
	CHECK_THROWS(sqtest6 += sqtest8);
	CHECK_THROWS(sqtest6 - sqtest8);
	CHECK_THROWS(sqtest6 -= sqtest8);
	CHECK_THROWS(sqtest6 * sqtest8);
	CHECK_THROWS(sqtest6 *= sqtest8);
	CHECK_THROWS_AS(sqtest6 * sqtest8, std::domain_error);

	CHECK_FALSE(sqtest6 == sqtest7);

	CHECK_THROWS((ConcreteSquareMatrix { "[1,77]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[1,77]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[1,77]" }));
	CHECK_THROWS(ConcreteSquareMatrix("{{7]]"));
	CHECK_THROWS((ConcreteSquareMatrix { "((1,2)(1,2))" }));

	CHECK_THROWS((ConcreteSquareMatrix { "[[*]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[8,]" }), "Invalid matrix");
	CHECK_THROWS((ConcreteSquareMatrix { " [[1,2][1,2.0]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "axxads" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[a1,a2]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[1,2,]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[1,2,3][1,2,3]]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[1,2,3][1,2,3][1,2]" }));
	CHECK_THROWS((ConcreteSquareMatrix { "[[1,2][1,2]]f" }));

	CHECK_THROWS_AS((ConcreteSquareMatrix { ConcreteSquareMatrix { "[8,]" } }),
			std::invalid_argument);
	CHECK_THROWS_WITH(ConcreteSquareMatrix("[[1,2][1,2]]f"), "Invalid matrix");

}

