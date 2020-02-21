#include "catch.hpp"
#include "valuation.hpp"
#include "varelement.hpp"
#include "symbolicmatrix.hpp"
#include "compositeelement.hpp"

TEST_CASE("Symbolicmatrix tests") {

	Valuation values;
	values.insert(std::pair<char, int>('a', 1));
	values.insert(std::pair<char, int>('b', 2));

	//testing constructors

	//empty constructor
	SymbolicSquareMatrix symtest1 { };
	CHECK(symtest1.toString() == "[]");

	//parametric constructor
	SymbolicSquareMatrix symtest2("[[a,2][b,4]]");
	CHECK(symtest2.toString() == "[[a,2][b,4]]");

	//copy constructor
	SymbolicSquareMatrix copy(symtest2);
	CHECK(copy.toString() == "[[a,2][b,4]]");

	//check if is matrix then returns same
	CHECK_NOTHROW(symtest2 = symtest2);
	CHECK_NOTHROW(symtest2 = std::move(symtest2));

	//testing +, -, * operations
	ConcreteSquareMatrix opertests{};
	SymbolicSquareMatrix opertest1("[[a,2][b,4]]");
	SymbolicSquareMatrix opertest2("[[a,2][b,4]]");

	opertest1 = opertest1 + opertest2;
	opertests = opertest1.evaluate(values);
	CHECK(opertests.toString() == "[[2,4][4,8]]");

	opertest1 = opertest1 - opertest2;
	opertests = opertest1.evaluate(values);
	CHECK(opertests.toString() == "[[1,2][2,4]]");

	opertest1 = opertest1 * opertest2;
	opertests = opertest1.evaluate(values);
	CHECK(opertests.toString() == "[[5,10][10,20]]");

	//test move constuctor
	SymbolicSquareMatrix move(std::move(symtest2));
	CHECK(move.toString() == "[[a,2][b,4]]");

	//test = operator
	symtest1 = symtest2;

	//transpose
	SymbolicSquareMatrix symtest3("[[7,10][15,22]]");
	symtest3.transpose();
	CHECK(symtest3.toString() == "[[7,15][10,22]]");

	//Testing move operator
	SymbolicSquareMatrix symmove = std::move(symtest3);
	CHECK(symmove.toString() == "[[7,15][10,22]]");

	//Testing print function
	std::ostringstream output_buffer;
	symmove.print(output_buffer);
	CHECK(output_buffer.str() == "[[7,15][10,22]]");

	//testing << operator
	std::stringstream str;
	str << symmove;
	CHECK(str.str() == "[[7,15][10,22]]");

}

TEST_CASE("Symbolicmatrix incorrect tests") {

	Valuation values;
	values.insert(std::pair<char, int>('a', 1));
	values.insert(std::pair<char, int>('b', 2));

	//different size matrices, check incorrect
	ConcreteSquareMatrix opertests{};
	SymbolicSquareMatrix opertest1("[[a,2,2][b,4,3][b,4,4]]");
	SymbolicSquareMatrix opertest2("[[a,2][b,4]]");

	CHECK_THROWS(opertest1 + opertest2);
	CHECK_THROWS(opertest1 - opertest2);
	CHECK_THROWS(opertest1 * opertest2);
	CHECK_THROWS_AS(opertest1 * opertest2, std::invalid_argument);

	//check false == operator
	SymbolicSquareMatrix sqtest6("[[1,2][3,4]]");
	SymbolicSquareMatrix sqtest7("[[1,2][5,4]]");
	CHECK_FALSE(sqtest6 == sqtest7);

	//check wrong values for evaluation
	SymbolicSquareMatrix wrongvalues("[[x,2,2][b,4,3][b,4,4]]");
	CHECK_THROWS(wrongvalues.evaluate(values));


	CHECK_THROWS((SymbolicSquareMatrix { "[1,77]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[1,77]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[1,77]" }));
	CHECK_THROWS(SymbolicSquareMatrix("{{7]]"));
	CHECK_THROWS((SymbolicSquareMatrix { "((1,2)(1,2))" }));

	CHECK_THROWS((SymbolicSquareMatrix { "[[*]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[8,]" }), "Invalid matrix");
	CHECK_THROWS((SymbolicSquareMatrix { " [[1,2][1,2.0]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "axxads" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[a1,a2]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[1,2,]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[1,2,3][1,2,3]]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[1,2,3][1,2,3][1,2]" }));
	CHECK_THROWS((SymbolicSquareMatrix { "[[1,2][1,2]]f" }));

	CHECK_THROWS_AS((SymbolicSquareMatrix { SymbolicSquareMatrix { "[8,]" } }),
			std::invalid_argument);
	CHECK_THROWS_WITH(SymbolicSquareMatrix("[[1,2][1,2]]f"), "Invalid matrix");

}

