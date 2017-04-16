#pragma once
#include <string>

using namespace std;

class MMU
{
public:
	MMU();
	virtual ~MMU();
	MMU(string, int, int);

	void setAction(string);
	void setVarID(int);
	void setToValue(int);

	string getAction();
	int getVarID();
	int getToValue(int);

private:
	string action;
	int varID;
	int toValue;
};

