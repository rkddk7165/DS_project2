#include "BpTree.h"
#include <string>

using namespace std;


BpTree::~BpTree(){}

bool BpTree::Insert(LoanBookData* newData) {
    if (!root) {
        // ��Ʈ ��尡 ���� ��� ���ο� ������ ��带 ����� ��Ʈ�� ����
        root = new BpTreeDataNode;

        //����ϸ�, �־��� �ڵ�� root�� ����Ű�� ��ü�� BpTreeDataNode�� �� ��ȯ�ϰ�, �� ��ü�� insertDataMap �Լ��� ȣ���Ͽ� ���ο� �����͸� �����Ϸ��� ���Դϴ�.
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }
    else {
        // ��Ʈ ��尡 �ִ� ��� ��Ʈ���� �����Ͽ� ������ ��带 ã�� ����
        BpTreeNode* node = searchDataNode(newData->getName());
        dynamic_cast<BpTreeDataNode*>(node)->insertDataMap(newData->getName(), newData);

        while (excessDataNode(node)) {
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

    //pDataNode�� BpTreeDataNode Ÿ������ ����ȯ�մϴ�. �̰��� ������ ��忡�� ������ �ʿ� �����ϱ� ���� ����˴ϴ�.
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);

    // ���ο� ������ ��� ����
    BpTreeDataNode* newDataNode = new BpTreeDataNode();

    // dataNode�� ������ �ʿ��� �߰� ������ ����Ű�� �ݺ��� mid�� �����ϰ� �ʱ�ȭ�մϴ�.
    auto mid = dataNode->getDataMap()->begin();

    //�߰� ���� �ݺ��� mid�� ������ ���� �߰����� �̵���ŵ�ϴ�. �̰��� ������ ��带 ������ ������ ���� �۾��Դϴ�.
    std::advance(mid, dataNode->getDataMap()->size() / 2);

    // ���ο� ������ ��忡 ���ҵ� ������ ���� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�����ؾ��� order = 3�̱� ������ for�� ���� �ϳ���
    for (auto it = mid; it != dataNode->getDataMap()->end(); it++) {
        newDataNode->insertDataMap(it->first, it->second);
    }

    // ���� ������ ��忡�� ���ҵ� ������ ����
    dataNode->getDataMap()->erase(mid, dataNode->getDataMap()->end());

    // ���ҵ� ������ ��� ���� (�����ͳ�峢���� ����� ��ũ�� ����Ʈ�̱� ����)
    newDataNode->setNext(dataNode->getNext());
    newDataNode->setPrev(dataNode);

    if (dataNode->getNext() != nullptr) {
        dataNode->getNext()->setPrev(newDataNode);
    }
    dataNode->setNext(newDataNode);

    // �θ� ��忡 ���ο� Ű�� �����ϰ� �ε����� ����
    if (dataNode->getParent() == nullptr) {
        // ��Ʈ ����� ��� ���ο� �ε��� ��带 �����Ͽ� ��Ʈ�� ������Ʈ
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, dataNode);
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        dataNode->setParent(newRoot);
        newDataNode->setParent(newRoot);
        root = newRoot;
    } else {
        BpTreeNode* parent = dataNode->getParent();

        // �θ� ��忡 ���ο� Ű�� �����մϴ�. �� ���ο� Ű�� newDataNode�� ù ��° ������ �� �׸��� Ű�� �����˴ϴ�. ------------> ��庰�� ���� ���°ǰ�...? �ʿ� ��ü�����Ͱ� ����Ǿ� �ִ°� �ƴѵ�??
        parent->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);

        // ���ο� Ű�� ������ ��, �θ� ��尡 �����ϴٸ� �θ� ��带 ����
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
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

    // ��Ʈ���� �����Ͽ� ������ ������ �������� Ž�� ����
    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // ���� ��带 �ε��� ���� ĳ����
        map<string, BpTreeNode*>::iterator it = pNode->getIndexMap()->begin();

        // �ε��� ��忡�� �ش� �������� ã�� ������ Ž��
        while (it != pNode->getIndexMap()->end()) {
            if (name < it->first) {
                break; // ���� �ε��� ��忡�� �������� ū Ű�� ã���� ����
            }
            it++;
        }

        // ã�� �ε��� ����� �ڽ����� �̵�
        pCur = it->second;
    }

    // ������ ��忡 �����ϸ� ��ȯ
    return pCur;
}

bool BpTree::searchBook(string name) {

}

bool BpTree::searchRange(string start, string end) {

}