#pragma once

#include <thread>

class Memory
{
public:
	Memory();
	Memory(int, int, int);
	virtual ~Memory();
	void setVarID(int);
	void setAgeint(int);
	void setValue(int);

	int getVarID();
	int getAge();
	int getValue();


private:
	int varID;
	int ageInt;
	int contentValue;

	std::thread * t;
};

