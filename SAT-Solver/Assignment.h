#pragma once

typedef int Bool;//-1 = false, 0 = unknown, 1 = true

class Assignment
{
public:
	Assignment(int size);
	~Assignment();

	void setValue(int i, Bool v);
	void unsetValue(int i);
	Bool getValue(int i);
private:
	int size;
	int* assignment;
};

