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
    // 데이터의 코드를 기반으로 leaf 노드를 찾음
    int code = newData->getCode();
    SelectionTreeNode* leafNode = findLeafNodeByCode(root, code);

    if (leafNode) {
        // leaf 노드에 연결된 heap에 데이터 삽입
        if (leafNode->getHeap()) {
            leafNode->getHeap()->Insert(newData);
            return true;
        }
        else {
            // leaf 노드에 연결된 heap이 없는 경우 에러 처리 또는 적절한 작업 수행
            return false;
        }
    }
    else {
        // leaf 노드를 찾지 못한 경우 에러 처리 또는 적절한 작업 수행
        return false;
    }
}


    // 코드를 기반으로 leaf 노드를 찾는 재귀 함수
    SelectionTreeNode* SelectionTree::findLeafNodeByCode(SelectionTreeNode* current, int code) {
        if (!current) {
            return nullptr;
        }

        if (!current->getLeftChild() && !current->getRightChild()) {
            // leaf 노드인 경우
            return current;
        }

        // 코드를 기반으로 왼쪽 또는 오른쪽 자식 노드로 이동
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
            // leaf 노드에 연결된 heap에 데이터 삽입
            if (leafNode->getHeap()) {
                leafNode->getHeap()->Insert(newData);
            }
            else {
                // leaf 노드에 연결된 heap이 없는 경우 새로운 heap을 생성하고 데이터 삽입
                leafNode->setHeap(new LoanBookHeap());
                leafNode->getHeap()->Insert(newData);
            }
        }
        else {
            // leaf 노드를 찾지 못한 경우 에러 처리 또는 적절한 작업 수행
            // 여기에 적절한 에러 처리를 추가하십시오.
        }
    }

    








