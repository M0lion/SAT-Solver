#include "Formula.h"

Formula::Formula(std::string input)
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
			if (newClauses[i]->varRange > varRange)
				varRange = newClauses[i]->varRange;

			i++;
			clauseStart = reader + 1;
		}
	}
	newClauses.push_back(new Clause(std::string(&input[clauseStart]), input.length() - clauseStart));
}

Formula::Formula(Formula* input)
{
	varRange = input->varRange;
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

Formula::~Formula()
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

Bool Formula::getValue(Assignment* a)
{
	Bool value = 1;

	for (int i = 0; i < newClauses.size(); i++)
	{
		Bool clause = newClauses[i]->getValue(a);
		if (clause == 0)
			value = 0;
		else if (clause == -1)
			return -1;
	}

	return value;
}

void Formula::Print()
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

Formula* Formula::Resolve(Formula* formula)
{
	Formula* newFormula = new Formula(formula);

	return newFormula;
}

bool Formula::SAT(Assignment* a)
{
	bool* localAssigns = new bool[varRange + 1];
	for (int i = 0; i <= varRange; i++)
	{
		localAssigns[i] = false;
	}

	if (a == nullptr)
		a = new Assignment(varRange);

	Bool val = getValue(a);

	if (val == 1)
		return true;
	else if (val == -1)
		return false;

	for (int i = 0; i < newClauses.size(); i++)
	{
		if (newClauses[i]->unassignedLiterals(a) == 1)
		{
			int lit = newClauses[i]->unassignedLiteral(a);
			localAssigns[abs(lit)] = true;
			a->setValue(abs(lit), lit > 0 ? 1 : -1);
		}
	}

	for (int i = 1; i <= varRange; i++)
	{
		if (a->getValue(i) == 0)
		{
			Bool hasVar = 0;
			for (int j = 0; j < newClauses.size(); j++)
			{
				if (newClauses[j]->getValue(a) != 0)
					continue;

				Bool clauseHasVar = newClauses[j]->hasVar(i);
				if (hasVar == 0)
					hasVar = clauseHasVar;
				else if (hasVar != clauseHasVar)
				{
					hasVar = 0;
					break;
				}
			}

			if (hasVar != 0)
			{
				a->setValue(i, hasVar == 1);
				localAssigns[i] = true;
			}
		}
	}

	int chosenLit = varRange;
	while (chosenLit != 0 && a->getValue(chosenLit) != 0)
		chosenLit--;

	bool result;
	if (chosenLit == 0)
	{
		result = getValue(a) == 1;
	}
	else
	{
		a->setValue(chosenLit, 1);
		result = SAT(a);
		if (result)
			return result;

		a->setValue(chosenLit, -1);
		result = SAT(a);
		if (result)
			return result;
	}

	a->unsetValue(chosenLit);
	for (int i = 1; i <= varRange; i++)
	{
		if (localAssigns[i])
			a->unsetValue(i);
	}

	return result;
}