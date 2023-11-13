#include "LoanBookHeap.h"

LoanBookHeap::LoanBookHeap() {
    root = nullptr;
}

LoanBookHeap::~LoanBookHeap() {
    
}



void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    if (!pN) {
        return;
    }

    while (pN->getParent() && (*pN->getBookData() < *pN->getParent()->getBookData())) {
        LoanBookHeapNode* parent = pN->getParent();
        LoanBookData* temp = parent->getBookData();
        parent->setBookData(pN->getBookData());
        pN->setBookData(temp);

        pN = parent;
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    if (!pN) {
        return;
    }

    while (pN) {
        LoanBookHeapNode* leftChild = pN->getLeftChild();
        LoanBookHeapNode* rightChild = pN->getRightChild();
        LoanBookHeapNode* minChild = nullptr;

        if (leftChild && rightChild) {
            // Determine the minimum of the two children.
            minChild = (*leftChild->getBookData() < *rightChild->getBookData()) ? leftChild : rightChild;
        }
        else if (leftChild) {
            minChild = leftChild;
        }
        else if (rightChild) {
            minChild = rightChild;
        }

        if (minChild && *minChild->getBookData() < *pN->getBookData()) {
            // Swap the data pointers to update the parent with the minimum child.
            LoanBookData* temp = pN->getBookData();
            pN->setBookData(minChild->getBookData());
            minChild->setBookData(temp);

            // Move to the minimum child's subtree for the next iteration.
            pN = minChild;
        }
        else {
            break;
        }
    }
}

bool LoanBookHeap::Insert(LoanBookData* data) {

    LoanBookHeapNode* newNode = new LoanBookHeapNode();

    newNode->setBookData(data);

    if (!root) {
        root = newNode;
    }
    else {
        if (!root->getLeftChild()) {
            root->setLeftChild(newNode);
        }
        else if (!root->getRightChild()) {
            root->setRightChild(newNode);
        }
        else {
            // Find the first available position in the heap.
            // You can implement your own logic here.
        }

        newNode->setParent(root);
        heapifyUp(newNode);

    }
    return true; // Insertion successful.
}






/*
#include "LoanBookHeap.h"

LoanBookHeap::LoanBookHeap() {
    this->root = NULL;
}

LoanBookHeap::~LoanBookHeap() {

}

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    if (!pN) {
        return;
    }
    while (pN->getParent() && (*pN->getBookData() < *pN->getParent()->getBookData())) {
        LoanBookHeapNode* parent = pN->getParent();
        LoanBookData* temp = parent->getBookData();
        parent->setBookData(pN->getBookData());
        pN->setBookData(temp);

        pN = parent;
    }
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    if (!pN) {
        return;
    }

    while (pN) {
        LoanBookHeapNode* leftChild = pN->getLeftChild();
        LoanBookHeapNode* rightChild = pN->getRightChild();
        LoanBookHeapNode* minChild = nullptr;

        if (leftChild && rightChild) {
            // Determine the minimum of the two children.
            minChild = (*leftChild->getBookData() < *rightChild->getBookData()) ? leftChild : rightChild;
        }
        else if (leftChild) {
            minChild = leftChild;
        }
        else if (rightChild) {
            minChild = rightChild;
        }

        if (minChild && *minChild->getBookData() < *pN->getBookData()) {
            // Swap the data pointers to update the parent with the minimum child.
            LoanBookData* temp = pN->getBookData();
            pN->setBookData(minChild->getBookData());
            minChild->setBookData(temp);

            // Move to the minimum child's subtree for the next iteration.
            pN = minChild;
        }
        else {
            break;
        }
    }
}


bool LoanBookHeap::Insert(LoanBookData* data) {
    LoanBookHeapNode* newNode = new LoanBookHeapNode();
    newNode->setBookData(data);

    if (!root) {
        root = newNode;
    }
    else {
        if (!root->getLeftChild()) {
            root->setLeftChild(newNode);
        }
        else if (!root->getRightChild()) {
            root->setRightChild(newNode);
        }
        else {
            // Find the first available position in the heap.
            // You can implement your own logic here.
        }

        newNode->setParent(root);
        heapifyUp(newNode);
    }

    return true; // Insertion successful.
}

*/