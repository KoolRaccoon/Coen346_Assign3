#include "MMU.h"



MMU::MMU()
{
}


MMU::~MMU()
{
}

MMU::MMU(string act, int id, int value)
{
	action = act;
	varID = id;
	toValue = value;
}

void MMU::setAction(string act)
{
	action = act;
}

void MMU::setVarID(int id)
{
	varID = id;
}

void MMU::setToValue(int value)
{
	toValue = value;
}

string MMU::getAction()
{
	return action;
}

int MMU::getVarID()
{
	return varID;
}

int MMU::getToValue(int)
{
	return toValue;
}
