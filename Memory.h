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
	void setAgeTimer(int);
	void incrementAgeTimer(int);

	int getVarID();
	int getAge();
	int getValue();
	int getAgeTimer();

private:
	int varID;
	int ageInt;
	int contentValue;
	int ageTimer;

	std::thread * t;
};

