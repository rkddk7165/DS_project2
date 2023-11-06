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

    bool found = false; // 트리에서 해당 도서를 찾았는지 여부를 나타내는 플래그.

    // Helper 함수를 정의하여 중위 순회로 도서를 검색하고 출력합니다.
    // 중위 순회를 사용하면 도서를 bookCode 순으로 출력할 수 있습니다.
   

    // 중위 순회를 시작합니다.
    inorderTraversal(root);

    if (!found) {
        // 해당 bookCode를 가진 도서를 찾지 못했을 경우에 대한 처리.
        *fout << "Book with Book Code " << bookCode << " not found." << std::endl;
        return false;
    }

    return true; // Printing successful.
}

void SelectionTree::inorderTraversal(SelectionTreeNode* node, int bookCode) {
    bool found = false;

    if (node) {
        inorderTraversal(node->getLeftChild());
        if (node->getBookData() == bookCode) { ////////////////////////////////////////////////////////////////////////////////////getbookdata는 전부인데 int bookcode와 비교.......
            // 해당 bookCode를 가진 도서를 찾았습니다.
            found = true;
            // 도서 정보를 출력합니다.
            *fout << node->getBookData() << endl;
            // 다른 도서 정보도 출력할 수 있습니다.
        }
        inorderTraversal(node->getRightChild());
    }
}

// 노드를 삭제할 때 필요한 노드 및 부모 노드를 추적하는 함수.
SelectionTreeNode* SelectionTree::findNodeToDelete(int bookCode, SelectionTreeNode* node, SelectionTreeNode* parent) {
    if (!node) {
        return nullptr; // 노드를 찾지 못한 경우.
    }
    if (node->getBookData()->getCode() == bookCode) {
        // 삭제할 노드를 찾은 경우.
        if (!node->getLeftChild() && !node->getRightChild()) {
            // 경우 1: 리프 노드인 경우.
            return node;
        }
        // 경우 2 및 3: 자식이 있는 경우.
        return node;
    }
    // 해당 노드에 대한 탐색 계속.
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

    

    // 삭제할 노드를 찾습니다.
    SelectionTreeNode* parent = nullptr;
    SelectionTreeNode* nodeToDelete = findNodeToDelete(bookCode, root, parent);

    if (!nodeToDelete) {
        // 삭제할 노드를 찾지 못한 경우.
        *fout << "Book with Book Code " << bookCode << " not found." << std::endl;
        return false;
    }

    if (!nodeToDelete->getLeftChild() && !nodeToDelete->getRightChild()) {
        // 경우 1: 리프 노드인 경우.
        if (parent) {
            if (parent->getLeftChild() == nodeToDelete) {
                parent->setLeftChild(nullptr);
            }
            else {
                parent->setRightChild(nullptr);
            }
        }
        else {
            // 루트 노드를 삭제하는 경우.
            root = nullptr;
        }
        delete nodeToDelete; // 노드 삭제.
    }
    else if (!nodeToDelete->getLeftChild() || !nodeToDelete->getRightChild()) {
        // 경우 2: 자식이 한 개인 경우.
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
            // 루트 노드를 삭제하는 경우.
            root = child;
        }
        delete nodeToDelete; // 노드 삭제.
    }
    else {
        // 경우 3: 자식이 두 개인 경우.
        // 왼쪽 서브트리에서 가장 큰 값을 찾아와 노드를 대체한 다음 해당 노드를 삭제합니다.
        SelectionTreeNode* replacement = nodeToDelete->getLeftChild();
        SelectionTreeNode* replacementParent = nodeToDelete;
        while (replacement->getRightChild()) {
            replacementParent = replacement;
            replacement = replacement->getRightChild();
        }
        // 삭제할 노드와 대체할 노드의 데이터를 교체합니다.
        nodeToDelete->setBookData(replacement->getBookData());
        // 대체할 노드를 삭제합니다.
        if (replacementParent == nodeToDelete) {
            replacementParent->setLeftChild(replacement->getLeftChild());
        }
        else {
            replacementParent->setRightChild(replacement->getLeftChild());
        }
        delete replacement; // 대체할 노드 삭제.
    }

    return true; // Deletion successful.
}









