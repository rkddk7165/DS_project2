#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode
{
private:
	//Declare mapdata as map with string and LoanBookData* as a pair
	map <string, LoanBookData*> mapData;

	//child pointer
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:

	//constructor
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}

	//desturctor
	~BpTreeDataNode() {

	}

	////Member function declaration of BpTreeDataNode class (Linked list pointers)
	void setNext(BpTreeNode* pN) { pNext = pN; }
	void setPrev(BpTreeNode* pN) { pPrev = pN; }
	BpTreeNode* getNext() { return pNext; }
	BpTreeNode* getPrev() { return pPrev; }

	//Insert a new key-value pair with string name as key and LoanBookData* value pN
	void insertDataMap(string name, LoanBookData* pN) {
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN));
	}

	//Function to check if it is a data node (override)
	virtual bool isDataNode() const override {
		return true; 
	}

	//a function to erase data from mapdata
	void deleteMap(string name) {
		mapData.erase(name);
	}
	map<string, LoanBookData*>* getDataMap() { return &mapData; }
};

#endif
