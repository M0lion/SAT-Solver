
#include "Clause.h"
#include <string>

#include "Formula.h"

int main()
{
	std::string clauseTest = "1 2 -3 -4 5 5 -3";
	Clause test(clauseTest, clauseTest.length());
	test.Print();
	printf("\n");

	Formula testFormula("");
	testFormula.Print();
	
	Assignment assignment(3);
	assignment.setValue(1, 1);
	assignment.setValue(2, 1);
	assignment.setValue(3, 1);
	printf("%d\n", testFormula.getValue(&assignment));

	bool res = testFormula.SAT();
	printf("%d\n", res);

	scanf_s("/n");
}