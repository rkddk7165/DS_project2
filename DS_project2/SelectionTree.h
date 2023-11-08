#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
    }
    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
};

/*#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
    }
    ~SelectionTree() {

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);
    SelectionTreeNode* findNodeToDelete(int bookCode, SelectionTreeNode* node, SelectionTreeNode* parent);
    void inorderTraversal(SelectionTreeNode* node, int bookCode);
};
*/