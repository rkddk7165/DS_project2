#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
	ifstream fin;
	ofstream flog;

	//BpTree* bptree;
public:
	Manager(int bpOrder)	//constructor
	{
		bptree = new BpTree(&flog, bpOrder);
		stree = new SelectionTree(&flog);
		

		/* You must fill here */
	}


	~Manager()//destructor
	{
		/* You must fill here */
	}

	


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