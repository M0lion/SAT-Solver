#include "Resolution.h"

Resolution::Resolution(std::string input)
{
	numberOfClauses = input.length() == 0 ? 0 : 1;
	isValid = numberOfClauses > 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ';')
			numberOfClauses++;
	}

	newClauses.reserve(numberOfClauses);
	int i = 0;
	int clauseStart = 0;
	for (int reader = 0; reader < input.length(); reader++)
	{
		if (input[reader] == ';')
		{
			newClauses.push_back(new Clause(std::string(&input[clauseStart]), reader - clauseStart));
			i++;
			clauseStart = reader + 1;
		}
	}
	newClauses.push_back(new Clause(std::string(&input[clauseStart]), input.length() - clauseStart));
}

Resolution::Resolution(Resolution* input)
{
	numberOfClauses = input->numberOfClauses;
	isValid = numberOfClauses > 0;
	clausesLength = numberOfClauses;
	clauses = new Clause*[clausesLength];
	int i = 0;
	for (int j = 0; j < input->clausesLength; j++)
	{
		clauses[i] = input->clauses[j];
		i++;
	}
	for (int j = 0; j < input->newClauses.size(); j++)
	{
		clauses[i] = input->newClauses[j];
		i++;
	}

	input->deleteClauses = false;
}

Resolution::~Resolution()
{
	if(deleteClauses)
	{
		if (clauses != nullptr)
		{
			for (int i = 0; i < numberOfClauses; i++)
			{
				delete(clauses[i]);
			}
		}
		for (int i = 0; i < newClauses.size(); i++)
		{
			delete(newClauses[i]);
		}
	}
	
	if(clauses != nullptr)
		delete(clauses);
}

void Resolution::Print()
{
	if (clauses != nullptr)
	{
		for (int i = 0; i < numberOfClauses; i++)
		{
			clauses[i]->Print();
			printf("; ");
		}
		printf("-");
	}

	for (int i = 0; i < newClauses.size(); i++)
	{
		newClauses[i]->Print();
		printf("; ");
	}

	printf("\n");
}

Resolution* Resolution::Resolve(Resolution* formula)
{
	Resolution* newFormula = new Resolution(formula);

	return newFormula;
}