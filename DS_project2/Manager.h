#pragma once

#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	//BpTree* bptree;

	//BpTree* bptree;
public:
	Manager(int bpOrder)	//constructor
	{
		/* You must fill here */
	}


	~Manager()//destructor
	{
		/* You must fill here */
	}

	ifstream fin;
	ofstream flog;


	void run(const char* command);
	bool LOAD();
	bool ADD();

};