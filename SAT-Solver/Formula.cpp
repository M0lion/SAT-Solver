#include "Formula.h"

Formula::Formula(std::string input)
{
	numberOfClauses = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ';')
			numberOfClauses++;
	}

	clauses.reserve(numberOfClauses);
	int i = 0;
	int clauseStart = 0;
	for (int reader = 0; reader < input.length(); reader++)
	{
		if (input[reader] == ';')
		{
			clauses.push_back(new Clause(std::string(&input[clauseStart]), reader - clauseStart));
			if (clauses[i]->varRange > varRange)
				varRange = clauses[i]->varRange;

			i++;
			clauseStart = reader + 1;
		}
	}
	clauses.push_back(new Clause(std::string(&input[clauseStart]), input.length() - clauseStart));
}

Formula::~Formula()
{
	for (int i = 0; i < clauses.size(); i++)
	{
		delete(clauses[i]);
	}
}

Bool Formula::getValue(Assignment* a)
{
	Bool value = 1;

	for (int i = 0; i < clauses.size(); i++)
	{
		Bool clause = clauses[i]->getValue(a);
		if (clause == 0)
			value = 0;
		else if (clause == -1)
			return -1;
	}

	return value;
}

void Formula::Print()
{
	for (int i = 0; i < clauses.size(); i++)
	{
		clauses[i]->Print();
		printf("; ");
	}

	printf("\n");
}

bool Formula::SAT(Assignment* a)
{
	if (numberOfClauses == 0)
		return false;

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

	for (int i = 0; i < clauses.size(); i++)
	{
		if (clauses[i]->unassignedLiterals(a) == 1)
		{
			int lit = clauses[i]->unassignedLiteral(a);
			localAssigns[abs(lit)] = true;
			a->setValue(abs(lit), lit > 0 ? 1 : -1);
		}
	}

	for (int i = 1; i <= varRange; i++)
	{
		if (a->getValue(i) == 0)
		{
			Bool hasVar = 0;
			for (int j = 0; j < clauses.size(); j++)
			{
				if (clauses[j]->getValue(a) != 0)
					continue;

				Bool clauseHasVar = clauses[j]->hasVar(i);
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