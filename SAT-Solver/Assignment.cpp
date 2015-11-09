#include "Assignment.h"
#include <cstdlib>

Assignment::Assignment(int size)
{
	this->size = size;
	assignment = new int[size + 1];
	for (int i = 0; i <= size; i++)
	{
		assignment[i] = 0;
	}
}

void Assignment::setValue(int i, Bool v)
{
	assignment[i] = v;
}

void Assignment::unsetValue(int i)
{
	assignment[i] = 0;
}

Bool Assignment::getValue(int term)
{
	return assignment[abs(term)] * (term < 0 ? -1 : 1);
}

Assignment::~Assignment()
{
	delete(assignment);
}
