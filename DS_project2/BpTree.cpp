#include "BpTree.h"
#include "LoanBookHeap.h"
#include "SelectionTreeNode.h"
#include <string>

using namespace std;

bool BpTree::Insert(LoanBookData* newData) {
    if (root == nullptr) {
        // 루트 노드가 없는 경우 새로운 데이터 노드를 만들어 루트로 설정
        root = new BpTreeDataNode;
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }
    else {
        // 루트 노드가 있는 경우 루트에서 시작하여 데이터 노드를 찾아 삽입
        BpTreeNode* node = searchDataNode(newData->getName());
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(node);

        // 데이터 노드에 이미 도서가 존재하는지 확인
        auto it = dataNode->getDataMap()->find(newData->getName());

        

        if (it != dataNode->getDataMap()->end()) {
            // 이미 존재하는 경우 대출 권수를 1 증가
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
            // 존재하지 않는 경우 데이터 노드에 삽입
            dataNode->insertDataMap(newData->getName(), newData);
            

            while (excessDataNode(node)) {
                // 데이터 노드가 과다할 경우 분할
                splitDataNode(node);
            }
        }
    }

    return true; // 삽입 성공
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

    //pDataNode를 BpTreeDataNode 타입으로 형변환합니다. 이것은 데이터 노드에서 데이터 맵에 접근하기 위해 수행.
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);

    // 새로운 데이터 노드 생성
    BpTreeDataNode* newDataNode = new BpTreeDataNode();

    // dataNode의 데이터 맵에서 중간 지점을 가리키는 반복자 mid를 선언하고 초기화합니다.
    auto mid = dataNode->getDataMap()->begin();

    //중간 지점 반복자 mid를 데이터 맵의 중간으로 이동시킵니다. //////////// 데이터 노드를 반으로 나누기 위한 작업
    advance(mid, dataNode->getDataMap()->size() / 2);

    // 새로운 데이터 노드에 분할된 데이터 복사 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////수정해야함 order = 3이기 때문에 for문 말고 하나만
    for (auto it = mid; it != dataNode->getDataMap()->end(); it++) {
        newDataNode->insertDataMap(it->first, it->second);
    }

    // 기존 데이터 노드에서 분할된 데이터 삭제
    dataNode->getDataMap()->erase(mid, dataNode->getDataMap()->end());

    // 분할된 데이터 노드 연결 (데이터노드끼리는 양방향 링크드 리스트이기 때문)
    newDataNode->setNext(dataNode->getNext());
    newDataNode->setPrev(dataNode);

    if (dataNode->getNext() != nullptr) {
        dataNode->getNext()->setPrev(newDataNode);
    }
    dataNode->setNext(newDataNode);

    // 부모 노드에 새로운 키를 삽입하고 인덱스를 연결
    if (dataNode->getParent() == nullptr) {
        // 루트 노드인 경우 새로운 인덱스 노드를 생성하여 루트를 업데이트
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        //newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, dataNode);
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        dataNode->setParent(newRoot);
        newDataNode->setParent(newRoot);
        newRoot->setMostLeftChild(dataNode);
        root = newRoot;
    } else {
        BpTreeNode* parent = dataNode->getParent();

        // 부모 노드에 새로운 키를 삽입합니다. 이 새로운 키는 newDataNode의 첫 번째 데이터 맵 항목의 키로 설정됩니다. ------------> 노드별로 맵을 갖는건가...? 맵에 전체데이터가 저장되어 있는게 아닌듯??
        parent->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);

        // 새로운 키를 삽입한 후, 부모 노드가 과다하다면 부모 노드를 분할
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}


void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // 주어진 노드 pIndexNode를 BpTreeIndexNode로 형변환
    BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(pIndexNode);

    // 새로운 인덱스 노드를 생성하여 오른쪽 반을 선언
    BpTreeIndexNode* newIndexNode = new BpTreeIndexNode();

    // 인덱스 노드의 중간 위치를 찾아서 mid 반복자를 초기화
    auto mid = indexNode->getIndexMap()->begin();
    mid++;

    string midName = mid->first;

    auto it = mid;
    it++;

    newIndexNode->insertIndexMap(it->first, it->second);
  

    
    newIndexNode->setMostLeftChild(mid->second);

    // 원래 인덱스 노드에서 중간 위치 이후의 키와 자식 포인터를 제거
    indexNode->getIndexMap()->erase(mid, indexNode->getIndexMap()->end());


    // 부모 노드에 새로운 키를 삽입하고 인덱스를 연결
    if (indexNode->getParent() == nullptr) {
        // 루트 노드인 경우 새로운 인덱스 노드를 생성하여 루트를 업데이트
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(midName, newIndexNode);
        indexNode->setParent(newRoot);
        newIndexNode->setParent(newRoot);
        newRoot->setMostLeftChild(indexNode);
        
       
        root = newRoot;
    }
    else {
        BpTreeNode* parent = indexNode->getParent();

        // 부모 노드에 새로운 키를 삽입합니다.
        parent->insertIndexMap(mid->first, newIndexNode);

        // 새로운 키를 삽입한 후, 부모 노드가 과다하다면 부모 노드를 분할
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;

    

    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // 현재 노드를 인덱스 노드로 캐스팅
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

    // 루트부터 시작하여 데이터 노드까지 내려가는 탐색 과정
    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // 현재 노드를 인덱스 노드로 캐스팅
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

    // 데이터 노드에 도달
    while (pCur != nullptr) {
        BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // 현재 노드를 데이터 노드로 캐스팅
        auto dataIt = pDataNode->getDataMap()->begin();

        // 데이터 노드에서 해당 도서명을 찾을 때까지 탐색
        while (dataIt != pDataNode->getDataMap()->end()) {
            if (name == dataIt->first) {
                // 해당 도서를 찾으면 정보를 출력
                *fout << "Book Found: " << dataIt->second->getName() << "/" << dataIt->second->getCode()
                    << "/" << dataIt->second->getAuthor() << "/" << dataIt->second->getYear() << "/"
                    << dataIt->second->getLoanCount() << endl;
                return true;
            }
            dataIt++;
        }

        // 다음 데이터 노드로 이동
        pCur = pDataNode->getNext();
    }

    // 책을 찾지 못한 경우
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
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pCur); // 현재 노드를 데이터 노드로 캐스팅
        for (const auto& entry : *(dataNode->getDataMap())) {
            *fout << entry.second->getName() << "/" << entry.second->getCode() << "/"
                << entry.second->getAuthor() << "/" << entry.second->getYear() << "/"
                << entry.second->getLoanCount() << endl;
        }

        // 다음 데이터 노드로 이동
        pCur = dataNode->getNext();
    }

    return true;
}






/*
while (pCur != nullptr) {
    BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // 현재 노드를 데이터 노드로 캐스팅
    map<string, LoanBookData*>::iterator dataIt = pDataNode->getDataMap()->begin();

    // 데이터 노드에서 해당 도서명을 찾을 때까지 탐색
    while (dataIt != pDataNode->getDataMap()->end()) {
        if (name < dataIt->first) {
            break; // 현재 데이터 노드에서 도서명보다 큰 키를 찾으면 종료
        }
        dataIt++;
    }

    // 삽입할 적절한 위치를 찾은 경우 반환
    if (dataIt != pDataNode->getDataMap()->end()) {
        return pCur;
    }

    // 다음 데이터 노드로 이동
    pCur = pDataNode->getNext();
}

return nullptr; // 삽입할 적절한 위치를 찾지 못한 경우
}
      */


      /*
      BpTreeNode* BpTree::searchDataNode(string name) {
          BpTreeNode* pCur = root;


          // 루트부터 시작하여 데이터 노드까지 내려가는 탐색 과정
          while (!pCur->isLeaf()) {
              BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // 현재 노드를 인덱스 노드로 캐스팅
              auto it = pNode->getIndexMap()->begin();

              // 인덱스 노드에서 해당 도서명을 찾을 때까지 탐색
              while (it != pNode->getIndexMap()->end()) {
                  if (name < it->first) {
                      break; // 현재 인덱스 노드에서 도서명보다 큰 키를 찾으면 종료
                  }
                  it++;
              }

              // 인덱스 노드에서 해당 도서명을 찾지 못한 경우
              if (it == pNode->getIndexMap()->end()) {
                  // 맨 마지막 인덱스의 자식으로 이동
                  it--;
                  pCur = it->second;
              }
              else {
                  // 찾은 인덱스 노드의 자식으로 이동
                  pCur = it->second;
              }

              while (!pCur->isLeaf()) {
                  BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // 현재 노드를 인덱스 노드로 캐스팅
                  map<string, BpTreeNode*>::iterator it = pNode->getIndexMap()->begin();
                  pCur = it->second; // 제일 왼쪽 자식으로 이동
              }

              // 데이터 노드에 도달
              while (pCur != nullptr) {
                  BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // 현재 노드를 데이터 노드로 캐스팅
                  map<string, LoanBookData*>::iterator dataIt = pDataNode->getDataMap()->begin();

                  // 데이터 노드에서 해당 도서명을 찾을 때까지 탐색
                  while (dataIt != pDataNode->getDataMap()->end()) {
                      if (name < dataIt->first) {
                          break; // 현재 데이터 노드에서 도서명보다 큰 키를 찾으면 종료
                      }
                      dataIt++;
                  }

                  // 삽입할 적절한 위치를 찾은 경우 반환
                  if (dataIt != pDataNode->getDataMap()->end()) {
                      return pCur;
                  }

                  // 다음 데이터 노드로 이동
                  pCur = pDataNode->getNext();
              }

              return nullptr; // 삽입할 적절한 위치를 찾지 못한 경우
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
        else { //현재 노드가 인덱스 노드인 경우
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
                  // 루트 노드가 없는 경우 새로운 데이터 노드를 만들어 루트로 설정
                  root = new BpTreeDataNode;

                  //요약하면, 주어진 코드는 root가 가리키는 객체를 BpTreeDataNode로 형 변환하고, 이 객체의 insertDataMap 함수를 호출하여 새로운 데이터를 삽입
                  dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
              }
              else {
                  // 루트 노드가 있는 경우 루트에서 시작하여 데이터 노드를 찾아 삽입
                  BpTreeNode* node = searchDataNode(newData->getName());
                  dynamic_cast<BpTreeDataNode*>(node)->insertDataMap(newData->getName(), newData);





                  while (excessDataNode(node)) {
                      // 데이터 노드가 과다할 경우 분할
                      splitDataNode(node);
                  }

              }

              return true; // 삽입 성공
          }
          */
