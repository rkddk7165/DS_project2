#include "SelectionTree.h"

bool SelectionTree::Insert(LoanBookData* newData) {
    SelectionTreeNode* newNode = new SelectionTreeNode();
    newNode->setBookData(newData);

    if (!root) {
        root = newNode;
    }
    else {
        SelectionTreeNode* current = root;
        SelectionTreeNode* parent = nullptr;

        // Traverse the tree to find the appropriate insertion point based on your criteria.
        // For example, you can compare book data to determine the insertion point.
        while (current) {
            parent = current;
            if (*newData < *(current->getBookData())) {
                current = current->getLeftChild();
            }
            else {
                current = current->getRightChild();
            }
        }

        // Insert the new node.
        if (*newData < *(parent->getBookData())) {
            parent->setLeftChild(newNode);
        }
        else {
            parent->setRightChild(newNode);
        }
    }

    return true; // Insertion successful.
}

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









