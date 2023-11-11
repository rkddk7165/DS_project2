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

	//종합적으로, 이 코드는 mapData라는 std::map에 문자열 키 name과 LoanBookData* 값 pN을 가지는 새로운 키-값 쌍을 삽입하는 작업을 수행합니다. 이렇게 하면 mapData에 새로운 데이터가 추가됩니다.
	void insertDataMap(string name, LoanBookData* pN) {
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN));
	}

	virtual bool isLeaf() const override {
		return true; // 데이터 노드는 리프 노드임
	}

	void deleteMap(string name) {
		mapData.erase(name);
	}
	map<string, LoanBookData*>* getDataMap() { return &mapData; }
};

#endif
