#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, LoanBookData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}
	~BpTreeDataNode() {

	}

	void setNext(BpTreeNode* pN) { pNext = pN; }
	void setPrev(BpTreeNode* pN) { pPrev = pN; }
	BpTreeNode* getNext() { return pNext; }
	BpTreeNode* getPrev() { return pPrev; }

	//����������, �� �ڵ�� mapData��� std::map�� ���ڿ� Ű name�� LoanBookData* �� pN�� ������ ���ο� Ű-�� ���� �����ϴ� �۾��� �����մϴ�. �̷��� �ϸ� mapData�� ���ο� �����Ͱ� �߰��˴ϴ�.
	void insertDataMap(string name, LoanBookData* pN) {
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN));
	}

	virtual bool isLeaf() const override {
		return true; // ������ ���� ���� �����
	}

	void deleteMap(string name) {
		mapData.erase(name);
	}
	map<string, LoanBookData*>* getDataMap() { return &mapData; }
};

#endif
