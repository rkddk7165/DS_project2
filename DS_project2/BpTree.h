#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;

	

public:
	//Constructor of BpTree class
	BpTree(ofstream* fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {};

	//Member function declaration of BpTree class
	bool		Insert(LoanBookData* newData);
	bool		isInsertError(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);

	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);
	bool printBook();
	bool Delete(LoanBookData* data);

};

#endif