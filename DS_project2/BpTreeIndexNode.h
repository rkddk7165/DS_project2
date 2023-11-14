#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
//template <class T>
class BpTreeIndexNode : public BpTreeNode {
private:

	////Declare mapdata as map with string and BpTreeNode* as a pair
	map <string, BpTreeNode*> mapIndex;

public:
	//constructor
	BpTreeIndexNode() {};
	//destructor
	~BpTreeIndexNode() {

	};

	//Insert a new key-value pair with string name as key and BpTreeNode* value pN
	void insertIndexMap(string name, BpTreeNode* pN) {
		mapIndex.insert(map<string, BpTreeNode*>::value_type(name, pN));
	}

	////Function to check if it is a data node (override)
	bool isDataNode() const override {
		return false;
	}

	//A function to erase data from mapdata
	void deleteMap(string name) {
		mapIndex.erase(name);
	}

	map <string, BpTreeNode*>* getIndexMap() { return &mapIndex; }

};

#endif