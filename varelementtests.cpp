#include "catch.hpp"
#include "valuation.hpp"
#include "varelement.hpp"
#include "compositeelement.hpp"
#include <sstream>

TEST_CASE("Varelement tests") {

	//testing constructors
	VariableElement test1 { };
	std::cout << test1.toString();
	CHECK(test1.getVal() == (char ) 0);
	VariableElement test2('a');
	CHECK(test2.toString() == "a");
	VariableElement test3(test2);
	CHECK(test3.toString() == "a");

	//test stringstream
	std::stringstream str;
	str << test3;
	CHECK(str.str() == "a");

	//test == operator
	CHECK(test2 == test3);

	//testing setters and getters
	CHECK(test3.getVal() == 'a');
	test3.setVal('b');
	CHECK(test3.getVal() == 'b');

	//testing clone
	std::unique_ptr<Element> vartestclone;
	vartestclone = test3.clone();
	CHECK(vartestclone.get()->toString() == test3.toString());

	//test evaluate function, throws error if key is not in map
	Valuation var_values;
	var_values.insert(std::pair<char, int>('a', 0));
	CHECK(test2.evaluate(var_values) == 0);
	CHECK_THROWS(test3.evaluate(var_values));

}

