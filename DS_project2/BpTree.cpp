#include "BpTree.h"
#include "LoanBookHeap.h"
#include "SelectionTreeNode.h"
#include <string>

using namespace std;

bool BpTree::Insert(LoanBookData* newData) {
    if (root == nullptr) {
        // ��Ʈ ��尡 ���� ��� ���ο� ������ ��带 ����� ��Ʈ�� ����
        root = new BpTreeDataNode;
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }
    else {
        // ��Ʈ ��尡 �ִ� ��� ��Ʈ���� �����Ͽ� ������ ��带 ã�� ����
        BpTreeNode* node = searchDataNode(newData->getName());
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(node);

        // ������ ��忡 �̹� ������ �����ϴ��� Ȯ��
        auto it = dataNode->getDataMap()->find(newData->getName());

        

        if (it != dataNode->getDataMap()->end()) {
            // �̹� �����ϴ� ��� ���� �Ǽ��� 1 ����
            it->second->updateCount();


            int code = (it->second->getCode()) / 100;
            int loanCount = it->second->getLoanCount();
            if (it->second->getLoanCount() > 2 && (it->second->getCode() == 000)) {

                
            }
            else if (it->second->getLoanCount() > 2 && (it->second->getCode() == 100)) {

                LoanBookHeap* code100Heap = new LoanBookHeap;
                code100Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 2 && (it->second->getCode() == 200)) {

                LoanBookHeap* code200Heap = new LoanBookHeap;
                code200Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 3 && (it->second->getCode() == 300)) {

                LoanBookHeap* code300Heap = new LoanBookHeap;
                code300Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 3 && (it->second->getCode() == 400)) {

                LoanBookHeap* code400Heap = new LoanBookHeap;
                code400Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 1 && (it->second->getCode() == 500)) {

                LoanBookHeap* code500Heap = new LoanBookHeap;
                code500Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 1 && (it->second->getCode() == 600)) {

                LoanBookHeap* code600Heap = new LoanBookHeap;
                code600Heap->Insert(newData);
            }
            else if (it->second->getLoanCount() > 1 && (it->second->getCode() == 700)) {

                LoanBookHeap* code700Heap = new LoanBookHeap;
                code700Heap->Insert(newData);
            }
            

        }
        else {
            // �������� �ʴ� ��� ������ ��忡 ����
            dataNode->insertDataMap(newData->getName(), newData);
            

            while (excessDataNode(node)) {
                // ������ ��尡 ������ ��� ����
                splitDataNode(node);
            }
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

    //pDataNode�� BpTreeDataNode Ÿ������ ����ȯ�մϴ�. �̰��� ������ ��忡�� ������ �ʿ� �����ϱ� ���� ����.
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);

    // ���ο� ������ ��� ����
    BpTreeDataNode* newDataNode = new BpTreeDataNode();

    // dataNode�� ������ �ʿ��� �߰� ������ ����Ű�� �ݺ��� mid�� �����ϰ� �ʱ�ȭ�մϴ�.
    auto mid = dataNode->getDataMap()->begin();

    //�߰� ���� �ݺ��� mid�� ������ ���� �߰����� �̵���ŵ�ϴ�. //////////// ������ ��带 ������ ������ ���� �۾�
    advance(mid, dataNode->getDataMap()->size() / 2);

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
        //newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, dataNode);
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        dataNode->setParent(newRoot);
        newDataNode->setParent(newRoot);
        newRoot->setMostLeftChild(dataNode);
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


void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // �־��� ��� pIndexNode�� BpTreeIndexNode�� ����ȯ
    BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(pIndexNode);

    // ���ο� �ε��� ��带 �����Ͽ� ������ ���� ����
    BpTreeIndexNode* newIndexNode = new BpTreeIndexNode();

    // �ε��� ����� �߰� ��ġ�� ã�Ƽ� mid �ݺ��ڸ� �ʱ�ȭ
    auto mid = indexNode->getIndexMap()->begin();
    mid++;

    string midName = mid->first;

    auto it = mid;
    it++;

    newIndexNode->insertIndexMap(it->first, it->second);
  

    
    newIndexNode->setMostLeftChild(mid->second);

    // ���� �ε��� ��忡�� �߰� ��ġ ������ Ű�� �ڽ� �����͸� ����
    indexNode->getIndexMap()->erase(mid, indexNode->getIndexMap()->end());


    // �θ� ��忡 ���ο� Ű�� �����ϰ� �ε����� ����
    if (indexNode->getParent() == nullptr) {
        // ��Ʈ ����� ��� ���ο� �ε��� ��带 �����Ͽ� ��Ʈ�� ������Ʈ
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(midName, newIndexNode);
        indexNode->setParent(newRoot);
        newIndexNode->setParent(newRoot);
        newRoot->setMostLeftChild(indexNode);
        
       
        root = newRoot;
    }
    else {
        BpTreeNode* parent = indexNode->getParent();

        // �θ� ��忡 ���ο� Ű�� �����մϴ�.
        parent->insertIndexMap(mid->first, newIndexNode);

        // ���ο� Ű�� ������ ��, �θ� ��尡 �����ϴٸ� �θ� ��带 ����
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;

    

    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // ���� ��带 �ε��� ���� ĳ����
        auto it = pNode->getIndexMap()->begin();
        if (pNode->getIndexMap()->size() == 1) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild(); // it->second->getMostLeftChild();
            }
            else if (name > it->first) {
                pCur = it->second;
            }
        }
        else if (pNode->getIndexMap()->size() == 2) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild(); //it->second->getMostLeftChild();
            }

            else if (it->first < name && (++it)->first > name) {
                pCur = (--it)->second;//it->second->getMostLeftChild();
            }
            else if ((++it)->first < name) {
                pCur = it->second;
            }
        }
    }
    return pCur;
}
    

bool BpTree::searchBook(string name) {
    BpTreeNode* pCur = root;

    // ��Ʈ���� �����Ͽ� ������ ������ �������� Ž�� ����
    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // ���� ��带 �ε��� ���� ĳ����
        auto it = pNode->getIndexMap()->begin();
        if (pNode->getIndexMap()->size() == 1) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild(); // it->second->getMostLeftChild();
            }
            else if (name > it->first) {
                pCur = it->second;
            }
        }
        else if (pNode->getIndexMap()->size() == 2) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild(); //it->second->getMostLeftChild();
            }

            else if (it->first < name && (++it)->first > name) {
                pCur = (--it)->second;//it->second->getMostLeftChild();
            }
            else if ((++it)->first < name) {
                pCur = it->second;
            }
        }
    }

    // ������ ��忡 ����
    while (pCur != nullptr) {
        BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // ���� ��带 ������ ���� ĳ����
        auto dataIt = pDataNode->getDataMap()->begin();

        // ������ ��忡�� �ش� �������� ã�� ������ Ž��
        while (dataIt != pDataNode->getDataMap()->end()) {
            if (name == dataIt->first) {
                // �ش� ������ ã���� ������ ���
                *fout << "Book Found: " << dataIt->second->getName() << "/" << dataIt->second->getCode()
                    << "/" << dataIt->second->getAuthor() << "/" << dataIt->second->getYear() << "/"
                    << dataIt->second->getLoanCount() << endl;
                return true;
            }
            dataIt++;
        }

        // ���� ������ ���� �̵�
        pCur = pDataNode->getNext();
    }

    // å�� ã�� ���� ���
    cout << "Book not found." << endl;
    return false;
}


bool BpTree::searchRange(string start, string end) {
    return true;
}

bool BpTree::printBook() {
    BpTreeNode* pCur = root;

    while (!pCur->isLeaf()) {
        pCur = pCur->getMostLeftChild();
    }
    while (pCur != nullptr) {
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pCur); // ���� ��带 ������ ���� ĳ����
        for (const auto& entry : *(dataNode->getDataMap())) {
            *fout << entry.second->getName() << "/" << entry.second->getCode() << "/"
                << entry.second->getAuthor() << "/" << entry.second->getYear() << "/"
                << entry.second->getLoanCount() << endl;
        }

        // ���� ������ ���� �̵�
        pCur = dataNode->getNext();
    }

    return true;
}






/*
while (pCur != nullptr) {
    BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // ���� ��带 ������ ���� ĳ����
    map<string, LoanBookData*>::iterator dataIt = pDataNode->getDataMap()->begin();

    // ������ ��忡�� �ش� �������� ã�� ������ Ž��
    while (dataIt != pDataNode->getDataMap()->end()) {
        if (name < dataIt->first) {
            break; // ���� ������ ��忡�� �������� ū Ű�� ã���� ����
        }
        dataIt++;
    }

    // ������ ������ ��ġ�� ã�� ��� ��ȯ
    if (dataIt != pDataNode->getDataMap()->end()) {
        return pCur;
    }

    // ���� ������ ���� �̵�
    pCur = pDataNode->getNext();
}

return nullptr; // ������ ������ ��ġ�� ã�� ���� ���
}
      */


      /*
      BpTreeNode* BpTree::searchDataNode(string name) {
          BpTreeNode* pCur = root;


          // ��Ʈ���� �����Ͽ� ������ ������ �������� Ž�� ����
          while (!pCur->isLeaf()) {
              BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // ���� ��带 �ε��� ���� ĳ����
              auto it = pNode->getIndexMap()->begin();

              // �ε��� ��忡�� �ش� �������� ã�� ������ Ž��
              while (it != pNode->getIndexMap()->end()) {
                  if (name < it->first) {
                      break; // ���� �ε��� ��忡�� �������� ū Ű�� ã���� ����
                  }
                  it++;
              }

              // �ε��� ��忡�� �ش� �������� ã�� ���� ���
              if (it == pNode->getIndexMap()->end()) {
                  // �� ������ �ε����� �ڽ����� �̵�
                  it--;
                  pCur = it->second;
              }
              else {
                  // ã�� �ε��� ����� �ڽ����� �̵�
                  pCur = it->second;
              }

              while (!pCur->isLeaf()) {
                  BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // ���� ��带 �ε��� ���� ĳ����
                  map<string, BpTreeNode*>::iterator it = pNode->getIndexMap()->begin();
                  pCur = it->second; // ���� ���� �ڽ����� �̵�
              }

              // ������ ��忡 ����
              while (pCur != nullptr) {
                  BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // ���� ��带 ������ ���� ĳ����
                  map<string, LoanBookData*>::iterator dataIt = pDataNode->getDataMap()->begin();

                  // ������ ��忡�� �ش� �������� ã�� ������ Ž��
                  while (dataIt != pDataNode->getDataMap()->end()) {
                      if (name < dataIt->first) {
                          break; // ���� ������ ��忡�� �������� ū Ű�� ã���� ����
                      }
                      dataIt++;
                  }

                  // ������ ������ ��ġ�� ã�� ��� ��ȯ
                  if (dataIt != pDataNode->getDataMap()->end()) {
                      return pCur;
                  }

                  // ���� ������ ���� �̵�
                  pCur = pDataNode->getNext();
              }

              return nullptr; // ������ ������ ��ġ�� ã�� ���� ���
          }
          }

          while (pCur) {
        if (pCur->isLeaf()) {
            BpTreeNode* dataNode = static_cast<BpTreeDataNode*> (pCur);
            auto dataMap = dataNode->getDataMap();


            auto it = dataMap->find(name);
            if (it != dataMap->end()) {

                *fout << it->second->getName() << "/" << it->second->getCode() << "/" << it->second->getAuthor() << "/" << it->second->getLoanCount() << endl;
                return true;
            }
            else {
                *fout << "ERROR" << endl;
                return false;
            }
        }
        else { //���� ��尡 �ε��� ����� ���
            BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(pCur);
            auto indexMap = indexNode->getIndexMap();

            auto it = indexMap->begin();
            while (it != indexMap->end() && name > it->first) {
                ++it;

        }

            if (it == indexMap->begin()) {

                pCur = indexNode;
            }
            else {
                pCur = it->second;
            }


        }
    }

    *fout << "ERROR" << endl;
    return false;

          */




          /*
          bool BpTree::Insert(LoanBookData* newData) {
              if (root == nullptr) {
                  // ��Ʈ ��尡 ���� ��� ���ο� ������ ��带 ����� ��Ʈ�� ����
                  root = new BpTreeDataNode;

                  //����ϸ�, �־��� �ڵ�� root�� ����Ű�� ��ü�� BpTreeDataNode�� �� ��ȯ�ϰ�, �� ��ü�� insertDataMap �Լ��� ȣ���Ͽ� ���ο� �����͸� ����
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
          */
