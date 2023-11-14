#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"


class LoanBookHeap
{
private:
    LoanBookHeapNode* root;

public:
    //constructor
    LoanBookHeap() {
        this->root = NULL;
    };

    //destructor
    ~LoanBookHeap() {

    }

    //Member function declaration of LoanBookHeap class
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);

    bool Insert(LoanBookData* data);
};