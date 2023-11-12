#include "SelectionTree.h"


bool SelectionTree::Delete() {
    return true;
}

bool SelectionTree::printBookData(int bookCode) {
    return true;
}



void SelectionTree::buildSelectionTree() {
    // ��Ʈ ���
    SelectionTreeNode* root = new SelectionTreeNode;

    // 1��° ����
    root->setLeftChild(new SelectionTreeNode());
    root->setRightChild(new SelectionTreeNode());

    // 2��° ����
    root->getLeftChild()->setLeftChild(new SelectionTreeNode());
    root->getLeftChild()->setRightChild(new SelectionTreeNode());
    root->getRightChild()->setLeftChild(new SelectionTreeNode());
    root->getRightChild()->setRightChild(new SelectionTreeNode());

    // 3��° ����
    
    SelectionTreeNode* code000Node = new SelectionTreeNode;
    root->getLeftChild()->getLeftChild()->setLeftChild(code000Node);
    

    SelectionTreeNode* code100Node = new SelectionTreeNode;
    root->getLeftChild()->getLeftChild()->setRightChild(code100Node);

    SelectionTreeNode* code200Node = new SelectionTreeNode;
    root->getLeftChild()->getRightChild()->setLeftChild(code200Node);

    SelectionTreeNode* code300Node = new SelectionTreeNode;
    root->getLeftChild()->getRightChild()->setRightChild(code300Node);

    SelectionTreeNode* code400Node = new SelectionTreeNode;
    root->getRightChild()->getLeftChild()->setLeftChild(code400Node);

    SelectionTreeNode* code500Node = new SelectionTreeNode;
    root->getRightChild()->getLeftChild()->setRightChild(code500Node);

    SelectionTreeNode* code600Node = new SelectionTreeNode;
    root->getRightChild()->getRightChild()->setLeftChild(code600Node);

    SelectionTreeNode* code700Node = new SelectionTreeNode;
    root->getRightChild()->getRightChild()->setRightChild(code700Node);

}

bool SelectionTree::Insert(LoanBookData* newData) {
    if (!root) {
        // ��Ʈ ���
        SelectionTreeNode* root = new SelectionTreeNode;

        // 1��° ����
        root->setLeftChild(new SelectionTreeNode());
        root->setRightChild(new SelectionTreeNode());

        // 2��° ����
        root->getLeftChild()->setLeftChild(new SelectionTreeNode());
        root->getLeftChild()->setRightChild(new SelectionTreeNode());
        root->getRightChild()->setLeftChild(new SelectionTreeNode());
        root->getRightChild()->setRightChild(new SelectionTreeNode());

        // 3��° ����

        SelectionTreeNode* code000Node = new SelectionTreeNode;
        root->getLeftChild()->getLeftChild()->setLeftChild(code000Node);


        SelectionTreeNode* code100Node = new SelectionTreeNode;
        root->getLeftChild()->getLeftChild()->setRightChild(code100Node);

        SelectionTreeNode* code200Node = new SelectionTreeNode;
        root->getLeftChild()->getRightChild()->setLeftChild(code200Node);

        SelectionTreeNode* code300Node = new SelectionTreeNode;
        root->getLeftChild()->getRightChild()->setRightChild(code300Node);

        SelectionTreeNode* code400Node = new SelectionTreeNode;
        root->getRightChild()->getLeftChild()->setLeftChild(code400Node);

        SelectionTreeNode* code500Node = new SelectionTreeNode;
        root->getRightChild()->getLeftChild()->setRightChild(code500Node);

        SelectionTreeNode* code600Node = new SelectionTreeNode;
        root->getRightChild()->getRightChild()->setLeftChild(code600Node);

        SelectionTreeNode* code700Node = new SelectionTreeNode;
        root->getRightChild()->getRightChild()->setRightChild(code700Node);
    }

    // ���ο� �����͸� ������ ��ġ�� ã�� ���� ���� ��ȸ�� Ž��
    SelectionTreeNode* current = root;
    SelectionTreeNode* parent = nullptr;

    while (current) {
        parent = current;
        if (newData->getName() < current->getBookData()->getName()) {
            current = current->getLeftChild();
        }
        else {
            current = current->getRightChild();
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
    int code = (newData->getCode()) / 100;
    int loanCount = newData->getLoanCount();

    if ((loanCount > 2 && code == 100) || (loanCount > 2 && code == 200) || (loanCount > 3 && code == 300) ||
        (loanCount > 3 && code == 400) || (loanCount > 1 && code == 500) || (loanCount > 1 && code == 600) ||
        (loanCount > 1 && code == 700)) {

        // ���ǿ� �´� ��� Min Heap�� �����ϰ� ����
        newNode->setHeap(new LoanBookHeap());
        newNode->getHeap()->Insert(newData);
    }

    return true;
}







/*
bool SelectionTree::printBookData(int bookCode) {
    if (!root) {
        return false; // The tree is empty.
    }

    bool found = false; // Ʈ������ �ش� ������ ã�Ҵ��� ���θ� ��Ÿ���� �÷���.

    // Helper �Լ��� �����Ͽ� ���� ��ȸ�� ������ �˻��ϰ� ����մϴ�.
    // ���� ��ȸ�� ����ϸ� ������ bookCode ������ ����� �� �ֽ��ϴ�.
   

    // ���� ��ȸ�� �����մϴ�.
    inorderTraversal(root);

    if (!found) {
        // �ش� bookCode�� ���� ������ ã�� ������ ��쿡 ���� ó��.
        *fout << "Book with Book Code " << bookCode << " not found." << std::endl;
        return false;
    }

    return true; // Printing successful.
}

void SelectionTree::inorderTraversal(SelectionTreeNode* node, int bookCode) {
    bool found = false;

    if (node) {
        inorderTraversal(node->getLeftChild());
        if (node->getBookData() == bookCode) { ////////////////////////////////////////////////////////////////////////////////////getbookdata�� �����ε� int bookcode�� ��.......
            // �ش� bookCode�� ���� ������ ã�ҽ��ϴ�.
            found = true;
            // ���� ������ ����մϴ�.
            *fout << node->getBookData() << endl;
            // �ٸ� ���� ������ ����� �� �ֽ��ϴ�.
        }
        inorderTraversal(node->getRightChild());
    }
}

// ��带 ������ �� �ʿ��� ��� �� �θ� ��带 �����ϴ� �Լ�.
SelectionTreeNode* SelectionTree::findNodeToDelete(int bookCode, SelectionTreeNode* node, SelectionTreeNode* parent) {
    if (!node) {
        return nullptr; // ��带 ã�� ���� ���.
    }
    if (node->getBookData()->getCode() == bookCode) {
        // ������ ��带 ã�� ���.
        if (!node->getLeftChild() && !node->getRightChild()) {
            // ��� 1: ���� ����� ���.
            return node;
        }
        // ��� 2 �� 3: �ڽ��� �ִ� ���.
        return node;
    }
    // �ش� ��忡 ���� Ž�� ���.
    parent = node;
    if (bookCode < node->getBookData()->getCode()) {
        return findNodeToDelete(bookCode, node->getLeftChild(), parent);
    }
    else {
        return findNodeToDelete(bookCode, node->getRightChild(), parent);
    }
}

bool SelectionTree::Delete() {
    if (!root) {
        return false; // The tree is empty.
    }

    

    // ������ ��带 ã���ϴ�.
    SelectionTreeNode* parent = nullptr;
    SelectionTreeNode* nodeToDelete = findNodeToDelete(bookCode, root, parent);

    if (!nodeToDelete) {
        // ������ ��带 ã�� ���� ���.
        *fout << "Book with Book Code " << bookCode << " not found." << std::endl;
        return false;
    }

    if (!nodeToDelete->getLeftChild() && !nodeToDelete->getRightChild()) {
        // ��� 1: ���� ����� ���.
        if (parent) {
            if (parent->getLeftChild() == nodeToDelete) {
                parent->setLeftChild(nullptr);
            }
            else {
                parent->setRightChild(nullptr);
            }
        }
        else {
            // ��Ʈ ��带 �����ϴ� ���.
            root = nullptr;
        }
        delete nodeToDelete; // ��� ����.
    }
    else if (!nodeToDelete->getLeftChild() || !nodeToDelete->getRightChild()) {
        // ��� 2: �ڽ��� �� ���� ���.
        SelectionTreeNode* child = (nodeToDelete->getLeftChild()) ? nodeToDelete->getLeftChild() : nodeToDelete->getRightChild();
        if (parent) {
            if (parent->getLeftChild() == nodeToDelete) {
                parent->setLeftChild(child);
            }
            else {
                parent->setRightChild(child);
            }
        }
        else {
            // ��Ʈ ��带 �����ϴ� ���.
            root = child;
        }
        delete nodeToDelete; // ��� ����.
    }
    else {
        // ��� 3: �ڽ��� �� ���� ���.
        // ���� ����Ʈ������ ���� ū ���� ã�ƿ� ��带 ��ü�� ���� �ش� ��带 �����մϴ�.
        SelectionTreeNode* replacement = nodeToDelete->getLeftChild();
        SelectionTreeNode* replacementParent = nodeToDelete;
        while (replacement->getRightChild()) {
            replacementParent = replacement;
            replacement = replacement->getRightChild();
        }
        // ������ ���� ��ü�� ����� �����͸� ��ü�մϴ�.
        nodeToDelete->setBookData(replacement->getBookData());
        // ��ü�� ��带 �����մϴ�.
        if (replacementParent == nodeToDelete) {
            replacementParent->setLeftChild(replacement->getLeftChild());
        }
        else {
            replacementParent->setRightChild(replacement->getLeftChild());
        }
        delete replacement; // ��ü�� ��� ����.
    }

    return true; // Deletion successful.
}
*/








