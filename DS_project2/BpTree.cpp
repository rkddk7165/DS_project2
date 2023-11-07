#include "BpTree.h"
#include <string>

using namespace std;


BpTree::~BpTree(){}

bool BpTree::Insert(LoanBookData* newData) {
    if (!root) {
        // ��Ʈ ��尡 ���� ��� ���ο� ������ ��带 ����� ��Ʈ�� ����
        root = new BpTreeDataNode;
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }
    else {
        // ��Ʈ ��尡 �ִ� ��� ��Ʈ���� �����Ͽ� ������ ��带 ã�� ����
        BpTreeNode* node = searchDataNode(newData->getName());
        dynamic_cast<BpTreeDataNode*>(node)->insertDataMap(newData->getName(), newData);

        if (excessDataNode(node)) {
            // ������ ��尡 ������ ��� ����
            splitDataNode(node);
        }
    }

    return true; // ���� ����
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

    // �߰� ���� ã�� ���ο� ��忡 �ű�� ���� ��忡�� ����
    auto middle = dataNode->getDataMap().begin();
    advance(middle, order / 2);

    for (auto it = middle; it != dataNode->getDataMap().end(); ++it) {
        newNode->insertDataMap(it->first, it->second);
    }

    for (auto it = middle; it != dataNode->getDataMap().end(); ++it) {
        dataNode->deleteMap(it->first);
    }

    // �߰� ���� ���� �ε��� ��忡 ����
    string middleKey = newNode->getDataMap().begin()->first;
    BpTreeIndexNode* parent = findParent(root, middleKey);

    if (!parent) {
        // ���ο� ��Ʈ ��尡 �ʿ��� ���
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

// ���� �ε��� ��带 ã�� ����� �Լ�
BpTreeIndexNode* BpTree::findParent(BpTreeNode* node, const string& key) {
    // �����ؾ� ��
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