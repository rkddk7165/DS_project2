#include "BpTree.h"
#include <string>

using namespace std;
/*
BpTree::BpTree(ofstream* fout, int order = 3) {
    root = NULL;
    this->order = order;
    this->fout = fout;
}
BpTree::~BpTree(){}
*/
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

    //중간 지점 반복자 mid를 데이터 맵의 중간으로 이동시킵니다. 이것은 데이터 노드를 반으로 나누기 위한 작업.
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
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, dataNode);
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        dataNode->setParent(newRoot);
        newDataNode->setParent(newRoot);
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

    // 주어진 노드 pIndexNode를 BpTreeIndexNode로 형변환합니다.
    BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(pIndexNode);

    // 새로운 인덱스 노드를 생성하여 오른쪽 반을 나타냅니다.
    BpTreeIndexNode* newIndexNode = new BpTreeIndexNode();

    // 인덱스 노드의 중간 위치를 찾아서 mid 반복자를 초기화합니다.
    auto mid = indexNode->getIndexMap()->begin();
    advance(mid, indexNode->getIndexMap()->size() / 2);

    // 중간 위치 이후의 키와 자식 포인터를 newIndexNode로 이동시킵니다.
    for (auto it = mid; it != indexNode->getIndexMap()->end(); it++) {
        newIndexNode->insertIndexMap(it->first, it->second);
    }

    // 원래 인덱스 노드에서 중간 위치 이후의 키와 자식 포인터를 제거합니다.
    indexNode->getIndexMap()->erase(mid, indexNode->getIndexMap()->end());

    // newIndexNode를 원래 인덱스 노드와 연결하고, 부모 노드에 중간 키를 삽입합니다.
    newIndexNode->setNext(indexNode->getNext());
    newIndexNode->setPrev(indexNode);
    if (indexNode->getNext()) {
        indexNode->getNext()->setPrev(newIndexNode);
    }
    indexNode->setNext(newIndexNode);

    // 부모 노드를 찾아서 중간 키를 삽입합니다.
    BpTreeNode* parent = indexNode->getParent();
    if (parent == nullptr) {
        // 부모가 없으면, 새로운 부모 노드를 생성하고 중간 키와 newIndexNode를 삽입합니다.
        BpTreeIndexNode* newParent = new BpTreeIndexNode();
        newParent->insertIndexMap(mid->first, indexNode);
        newParent->insertIndexMap(newIndexNode->getIndexMap()->begin()->first, newIndexNode);
        indexNode->setParent(newParent);
        newIndexNode->setParent(newParent);
        root = newParent;
    }
    else {
        // 그렇지 않으면, 중간 키를 부모 노드에 삽입하고, 부모가 과다한지 확인한 후 필요에 따라 부모 노드를 분할합니다.
        parent->insertIndexMap(mid->first, newIndexNode);
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}



BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;

    // 루트부터 시작하여 데이터 노드까지 내려가는 탐색 과정
    while (!pCur->isLeaf()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur); // 현재 노드를 인덱스 노드로 캐스팅
        map<string, BpTreeNode*>::iterator it = pNode->getIndexMap()->begin();

        // 인덱스 노드에서 해당 도서명을 찾을 때까지 탐색
        while (it != pNode->getIndexMap()->end()) {
            if (name < it->first) {
                break; // 현재 인덱스 노드에서 도서명보다 큰 키를 찾으면 종료
            }
            it++;
        }

        // 찾은 인덱스 노드의 자식으로 이동
        pCur = it->second;
    }

    // 데이터 노드에 도달하면 반환
    return pCur;
}

bool BpTree::searchBook(string name) {
    BpTreeNode* pCur = root;

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

}

bool BpTree::searchRange(string start, string end) {
    return true;
}