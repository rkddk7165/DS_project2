#pragma once
#include "LoanBookData.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:

	//constructor
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	//destructor
	~BpTreeNode() {

	}
	//Member function declaration of BpTreeNode class
	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }


	//virtual function to be implemented in derived classes (BpTreeDataNode, BpTreeIndexNode)
	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(string n, LoanBookData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	virtual bool isDataNode() const = 0;

	virtual map<string, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<string, LoanBookData*>* getDataMap() { return {}; }

};