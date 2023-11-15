#include "SelectionTree.h"


bool SelectionTree::Delete() {
    return true;
}

bool SelectionTree::printBookData(int bookCode) {
    return true;
}



void SelectionTree::buildSelectionTree() {
    root = new SelectionTreeNode;

    SelectionTreeNode* leftChild = new SelectionTreeNode();
    SelectionTreeNode* rightChild = new SelectionTreeNode();

    root->setLeftChild(leftChild);
    root->setRightChild(rightChild);

    leftChild->setParent(root);
    rightChild->setParent(root);

    SelectionTreeNode* leftLeftChild = new SelectionTreeNode();
    SelectionTreeNode* leftRightChild = new SelectionTreeNode();
    SelectionTreeNode* rightLeftChild = new SelectionTreeNode();
    SelectionTreeNode* rightRightChild = new SelectionTreeNode();

    leftChild->setLeftChild(leftLeftChild);
    leftChild->setRightChild(leftRightChild);
    rightChild->setLeftChild(rightLeftChild);
    rightChild->setRightChild(rightRightChild);

    leftLeftChild->setParent(leftChild);
    leftRightChild->setParent(leftChild);
    rightLeftChild->setParent(rightChild);
    rightRightChild->setParent(rightChild);

    SelectionTreeNode* code000Node = new SelectionTreeNode;
    leftLeftChild->setLeftChild(code000Node);
    code000Node->setParent(leftLeftChild);

    SelectionTreeNode* code100Node = new SelectionTreeNode;
    leftLeftChild->setRightChild(code100Node);
    code100Node->setParent(leftLeftChild);

    SelectionTreeNode* code200Node = new SelectionTreeNode;
    leftRightChild->setLeftChild(code200Node);
    code200Node->setParent(leftRightChild);

    SelectionTreeNode* code300Node = new SelectionTreeNode;
    leftRightChild->setRightChild(code300Node);
    code300Node->setParent(leftRightChild);

    SelectionTreeNode* code400Node = new SelectionTreeNode;
    rightLeftChild->setLeftChild(code400Node);
    code400Node->setParent(rightLeftChild);

    SelectionTreeNode* code500Node = new SelectionTreeNode;
    rightLeftChild->setRightChild(code500Node);
    code500Node->setParent(rightLeftChild);

    SelectionTreeNode* code600Node = new SelectionTreeNode;
    rightRightChild->setLeftChild(code600Node);
    code600Node->setParent(rightRightChild);

    SelectionTreeNode* code700Node = new SelectionTreeNode;
    rightRightChild->setRightChild(code700Node);
    code700Node->setParent(rightRightChild);
}

bool SelectionTree::Insert(LoanBookData* newData) {
    

    // ���ο� �����͸� ������ ��ġ�� ã�� ���� ���� ��ȸ�� Ž��
    SelectionTreeNode* pCur = root;
    SelectionTreeNode* parent = nullptr;

    while (pCur) {
        parent = pCur;
        if (newData->getName() < pCur->getBookData()->getName()) {
            pCur = pCur->getLeftChild();
        }
        else {
            pCur = pCur->getRightChild();
        }
    }

    // ���ο� ��� ����
    SelectionTreeNode* newNode = new SelectionTreeNode();
    newNode->setBookData(newData);

    // �θ�� ����
    newNode->setParent(parent);

    if (newData->getName() < parent->getBookData()->getName()) {
        parent->setLeftChild(newNode);
    }
    else {
        parent->setRightChild(newNode);
    }

    // Min Winner Tree ������ �����ϵ��� ����
    while (newNode->getParent() && newNode->getBookData()->getName() < newNode->getParent()->getBookData()->getName()) {
        // �θ���� �� �񱳸� ���� Min Winner Tree�� ����
        LoanBookData* temp = newNode->getBookData();
        newNode->setBookData(newNode->getParent()->getBookData());
        newNode->getParent()->setBookData(temp);

        newNode = newNode->getParent();
    }
    
    newNode->setHeap(new LoanBookHeap());


    return true;
}



    








