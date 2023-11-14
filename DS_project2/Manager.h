#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:

	//instances
	char* cmd;
	BpTree* bptree;
	
	ifstream fin;
	ofstream flog;

public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog, bpOrder);
	}


	~Manager()//destructor
	{
		delete bptree;
	}

	

	//Member function declaration of Manager class (command)
	void run(const char* command);
	bool LOAD();
	bool ADD(string addData);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST();

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(string command);

};