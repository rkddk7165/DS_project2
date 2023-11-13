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
    
    buildSelectionTree();
    // �������� �ڵ带 ������� leaf ��带 ã��
    int code = newData->getCode();
    SelectionTreeNode* leafNode = findLeafNodeByCode(root, code);

    if (leafNode) {
        // leaf ��忡 ����� heap�� ������ ����
        if (leafNode->getHeap()) {
            leafNode->getHeap()->Insert(newData);
            return true;
        }
        else {
            // leaf ��忡 ����� heap�� ���� ��� ���� ó�� �Ǵ� ������ �۾� ����
            return false;
        }
    }
    else {
        // leaf ��带 ã�� ���� ��� ���� ó�� �Ǵ� ������ �۾� ����
        return false;
    }
}


    // �ڵ带 ������� leaf ��带 ã�� ��� �Լ�
    SelectionTreeNode* SelectionTree::findLeafNodeByCode(SelectionTreeNode* current, int code) {
        if (!current) {
            return nullptr;
        }

        if (!current->getLeftChild() && !current->getRightChild()) {
            // leaf ����� ���
            return current;
        }

        // �ڵ带 ������� ���� �Ǵ� ������ �ڽ� ���� �̵�
        if (code == 000) {
            return findLeafNodeByCode(current->getLeftChild(), code);
        }
        else {
            return findLeafNodeByCode(current->getRightChild(), code);
        }
    }

    void SelectionTree::InsertToHeap(int heapCode, LoanBookData* newData) {
        SelectionTreeNode* leafNode = findLeafNodeByCode(root, heapCode);
        if (leafNode) {
            // leaf ��忡 ����� heap�� ������ ����
            if (leafNode->getHeap()) {
                leafNode->getHeap()->Insert(newData);
            }
            else {
                // leaf ��忡 ����� heap�� ���� ��� ���ο� heap�� �����ϰ� ������ ����
                leafNode->setHeap(new LoanBookHeap());
                leafNode->getHeap()->Insert(newData);
            }
        }
        else {
            // leaf ��带 ã�� ���� ��� ���� ó�� �Ǵ� ������ �۾� ����
            // ���⿡ ������ ���� ó���� �߰��Ͻʽÿ�.
        }
    }

    








