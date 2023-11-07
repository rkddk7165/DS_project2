#include "BpTree.h"
#include <string>

using namespace std;


BpTree::~BpTree(){}

bool BpTree::Insert(LoanBookData* newData) {
    if (!root) {
        // 루트 노드가 없는 경우 새로운 데이터 노드를 만들어 루트로 설정
        root = new BpTreeDataNode;
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }
    else {
        // 루트 노드가 있는 경우 루트에서 시작하여 데이터 노드를 찾아 삽입
        BpTreeNode* node = searchDataNode(newData->getName());
        dynamic_cast<BpTreeDataNode*>(node)->insertDataMap(newData->getName(), newData);

        if (excessDataNode(node)) {
            // 데이터 노드가 과다할 경우 분할
            splitDataNode(node);
        }
    }

    return true; // 삽입 성공
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);
    BpTreeDataNode* newNode = new BpTreeDataNode(order);

    // 중간 값을 찾아 새로운 노드에 옮기고 기존 노드에서 삭제
    auto middle = dataNode->getDataMap().begin();
    advance(middle, order / 2);

    for (auto it = middle; it != dataNode->getDataMap().end(); ++it) {
        newNode->insertDataMap(it->first, it->second);
    }

    for (auto it = middle; it != dataNode->getDataMap().end(); ++it) {
        dataNode->deleteMap(it->first);
    }

    // 중간 값을 상위 인덱스 노드에 삽입
    string middleKey = newNode->getDataMap().begin()->first;
    BpTreeIndexNode* parent = findParent(root, middleKey);

    if (!parent) {
        // 새로운 루트 노드가 필요한 경우
        parent = new BpTreeIndexNode(order);
        parent->insertIndexMap(middleKey, dataNode);
        parent->setKey(dataNode, middleKey);
        parent->setKey(newNode, newNode->getDataMap().begin()->first);
        root = parent;
    }
    else {
        parent->insertIndexMap(middleKey, newNode);
        parent->setKey(newNode, newNode->getDataMap().begin()->first);
    }
}

// 상위 인덱스 노드를 찾는 도우미 함수
BpTreeIndexNode* BpTree::findParent(BpTreeNode* node, const string& key) {
    // 구현해야 함
    return nullptr;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {

}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;

	return pCur;
}

bool BpTree::searchBook(string name) {

}

bool BpTree::searchRange(string start, string end) {

}