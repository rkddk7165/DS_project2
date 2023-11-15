#include "BpTree.h"
#include "LoanBookHeap.h"
#include <string>

using namespace std;

//Function to insert datas of a new book into the b+ tree
bool BpTree::Insert(LoanBookData* newData) {
    //If there is no root node, create a new data node and set it as the root.
    if (root == nullptr) {
        root = new BpTreeDataNode;

        //Casting BpTreeNode type to BpTreeDataNode type
        dynamic_cast<BpTreeDataNode*>(root)->insertDataMap(newData->getName(), newData);
    }

    else {
        // If there is a root node, start from the root and find and insert data nodes
        BpTreeNode* node = searchDataNode(newData->getName());
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(node);

        // Declare iterator to check if a book already exists in the data node
        auto it = dataNode->getDataMap()->find(newData->getName());


        // If a book already exists in the data node
        if (it != dataNode->getDataMap()->end()) {
            
            it->second->updateCount(); //Increase loandata by 1 without inserting new data

            //Save code and loancount to check loan disqualification
            int code = (it->second->getCode());
            int loanCount = it->second->getLoanCount();

            if ((loanCount > 2 && code == 000) || (loanCount > 2 && code == 100) || (loanCount > 2 && code == 200) || 
                (loanCount > 3 && code == 300) || (loanCount > 3 && code == 400) || (loanCount > 1 && code == 500) || 
                (loanCount > 1 && code == 600) || (loanCount > 1 && code == 700)) {

                LoanBookHeap* newheap = new LoanBookHeap;
                newheap->Insert(newData);

                Delete(newData);
            }
        }
        
        //If newData does not exist
        else {
            //If any of the data does not exist or the length of book name is more than 50 characters, returns false.
            if (!isInsertError(newData)) {
                return false;
            }

            // Insert into data node if it does not exist
            dataNode->insertDataMap(newData->getName(), newData);


            while (excessDataNode(node)) {
                // Split when data in a data node exceeds 3
                splitDataNode(node);
            }
        }
    

    return true; // Insert successfully
}
    }

//Function to check if an insertion error occurs
bool BpTree::isInsertError(LoanBookData* newData) {
    // Check if the book name is less than 50 characters
    if (newData->getName().length() >= 50) {
        return false;
    }

    // Check if the code is NULL
   // if (newData->getCode() == NULL) {
   //     return false;
    //}

    // Check if the author is empty
    if (newData->getAuthor().empty()) {
        return false;
    }

    // Check if the publication year is NULL
    if (newData->getYear() == NULL) {
        return false;
    }

    return true;
}





//Check if the data in the data node exceeds 2
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    if (pDataNode->getDataMap()->size() > order - 1) return true; //order is equal to the number of elements 
    else return false;
}

//Check if the data in the index node exceeds 2
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    if (pIndexNode->getIndexMap()->size() > order - 1)return true; //order is equal to the number of elements 
    else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {

    //Convert pDataNode to BpTreeDataNode type. This is done to access the data map from the data node
    BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pDataNode);

    // Create a new data node
    BpTreeDataNode* newDataNode = new BpTreeDataNode();

    // Declare and initialize an iterator mid that points to a midpoint in the dataNode's data map
    auto mid = dataNode->getDataMap()->begin();

    //Move the midpoint iterator mid to the middle of the data map. Operation to split a data node in half
    mid++;


    // Copy split data to new data node
    for (auto it = mid; it != dataNode->getDataMap()->end(); it++) {
        newDataNode->insertDataMap(it->first, it->second);
    }

    // Delete split data from existing data node
    dataNode->getDataMap()->erase(mid, dataNode->getDataMap()->end());


    // Connect divided data nodes (because data nodes are bidirectional linked lists)
    newDataNode->setNext(dataNode->getNext());
    newDataNode->setPrev(dataNode);

    if (dataNode->getNext() != nullptr) {
        dataNode->getNext()->setPrev(newDataNode);
    }
    dataNode->setNext(newDataNode);

    // Insert new key into parent node and concatenate index
    if (dataNode->getParent() == nullptr) {


        // If it is a root node, update the root by creating a new index node
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        dataNode->setParent(newRoot);
        newDataNode->setParent(newRoot);
        newRoot->setMostLeftChild(dataNode);
        root = newRoot;
    }

    //If it is not the root node
    else {
        BpTreeNode* parent = dataNode->getParent();

        // Insert a new key into the parent node and set the pointer of the parent node of newDataNode
        parent->insertIndexMap(newDataNode->getDataMap()->begin()->first, newDataNode);
        newDataNode->setParent(parent);


        // After inserting a new key, if there are too many parent nodes, split the parent node
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}


void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // Convert the given node pIndexNode to BpTreeIndexNode
    BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(pIndexNode);

    // Create a new index node
    BpTreeIndexNode* newIndexNode = new BpTreeIndexNode();


    // Find the middle position of the index node and initialize the mid iterator
    auto mid = indexNode->getIndexMap()->begin();
    mid++;

    //Save midName to construct a new index node
    string midName = mid->first;

    
    auto it = mid;
    it++; //it points to the last data

    //Insert last data into newIndexNode
    newIndexNode->insertIndexMap(it->first, it->second);


    //Set the child of mid to MostLeftChild of newIndexNode
    newIndexNode->setMostLeftChild(mid->second);

    // Remove key and child pointers after the middle position from the original index node
    indexNode->getIndexMap()->erase(mid);
    indexNode->getIndexMap()->erase(it);

    // Insert a new key into the parent node and connect the index to the pointer
    if (indexNode->getParent() == nullptr) {


        // If it is a root node, update the root by creating a new index node
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(midName, newIndexNode);
        indexNode->setParent(newRoot);
        newIndexNode->setParent(newRoot);
        newRoot->setMostLeftChild(indexNode);

        root = newRoot;
    }

    //If the root node already exists, insert mid data into the root node and set newIndexNode as the second pointer
    else {
        BpTreeNode* parent = indexNode->getParent();

        // Insert new key into parent node
        parent->insertIndexMap(midName, newIndexNode);

        // After inserting a new key, if the data of the parent node exceeds 2, split the parent node
        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

//Function to find the data node corresponding to the name received as an argument.
BpTreeNode* BpTree::searchDataNode(string name) {
    BpTreeNode* pCur = root;


    //While the node pointed to by pCur is an index node
    while (!pCur->isDataNode()) {

        // Cast the current node to the index node
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur);

        //Store the first data of the root node's indexmap in the iterator
        auto it = pNode->getIndexMap()->begin();

        //If the data of the index node pointed to by pNode is 1
        if (pNode->getIndexMap()->size() == 1) {

            //If the name received as an argument is smaller than the name of iterator it, change it to point to the mostleftchild of the indexnode
            if (name < it->first) {
                pCur = pNode->getMostLeftChild();
            }

            //If the name received as an argument is greater than the name of iterator it, change it to point to the second child pointer of the indexnode.
            else if (name >= it->first) {
                pCur = it->second;
            }
        }

        //If the data of the index node pointed to by pNode is 2
        else if (pNode->getIndexMap()->size() == 2) {

            //If the name received as an argument is smaller than the name of iterator it, change it to point to the mostleftchild of the indexnode
            if (name < it->first) {
                pCur = pNode->getMostLeftChild();
            }

            //If the name received as an argument is larger than the first data of the indexnode and smaller than the second data, moves pointer to the second child pointer of the first data.
            else if (it->first <= name && (++it)->first > name) {
                pCur = (--it)->second;
            }

            
            //If the name received as an argument is greater than the name of iterator it, change it to point to the second child pointer of the indexnode.
            else if ((it)->first <= name) {
                pCur = it->second;
            }
        }
    }

    //If pCur points to a data node, return pCur
    return pCur;
}

//A function to find the data of a data node that has the name received as an argument as the book name.
bool BpTree::searchBook(string name) {
    BpTreeNode* pCur = root;

    // Navigation process starting from the root and going down to the data node (same as navigation of searchDataNode)
    while (!pCur->isDataNode()) {
        BpTreeIndexNode* pNode = dynamic_cast<BpTreeIndexNode*>(pCur);
        auto it = pNode->getIndexMap()->begin();
        if (pNode->getIndexMap()->size() == 1) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild();
            }
            else if (name > it->first) {
                pCur = it->second;
            }
        }
        else if (pNode->getIndexMap()->size() == 2) {

            if (name < it->first) {
                pCur = pNode->getMostLeftChild();
            }

            else if (it->first < name && (++it)->first > name) {
                pCur = (--it)->second;
            }
            else if ((++it)->first < name) {
                pCur = it->second;
            }
        }
    }

    // Reach data node
    while (pCur != nullptr) {
        BpTreeDataNode* pDataNode = dynamic_cast<BpTreeDataNode*>(pCur); // Cast the current node to BpTreeDatNode
        auto it = pDataNode->getDataMap()->begin();

        // Search until the corresponding book name is found in the data node
        while (it != pDataNode->getDataMap()->end()) {
            if (name == it->first) {

                // Print data when the corresponding book is found
                *fout << "========SEARCH_BP========" << endl << it->second->getName() << "/" << it->second->getCode()
                    << "/" << it->second->getAuthor() << "/" << it->second->getYear() << "/"
                    << it->second->getLoanCount() << endl << "==========================" << endl << endl;
                return true;
            }
            //move to the next data for that datanode
            it++;
        }

        // move to next data node
        pCur = pDataNode->getNext();
    }

    // If the book is not found
    return false;
}

//A function that outputs all book data within the range received as arguments.
bool BpTree::searchRange(string start, string end) {

    //Call the searchDataNode function to move to the data node corresponding to string start
    BpTreeNode* pSearch = searchDataNode(start);

    //pNode moves to the last data node and searches.
    for (auto pNode = pSearch; pNode != nullptr; pNode = pNode->getNext()) {

        //Searches data until the end is reached within the node pointed to by pNode.
        for (auto it = pNode->getDataMap()->begin(); it != pNode->getDataMap()->end(); it++) {

            //If the iterator name is smaller than string start, it is not output.
            if (it->first < start) {
                continue;
            }

            //If the iterator name is greater than string end
            else if (it->first > end) {

                //If the first letter of the book name of iterator it is not equal to string end, the loop ends.
                auto found = it->first.find(end);
                if (found != 0) {
                    break;
                }
            }
            *fout << it->second->getName() << "/" << it->second->getCode() << "/" << it->second->getAuthor() << "/" << it->second->getYear() << "/" << it->second->getLoanCount() << endl;
        }
    }
    return true; 
}



// A Function to output all data in BpTree
bool BpTree::printBook() {
    BpTreeNode* pCur = root;

    //Move to the leftmost data node
    while (!pCur->isDataNode()) {
        pCur = pCur->getMostLeftChild();
    }

    // Iterate through Data nodes
    while (pCur != nullptr) {
        BpTreeDataNode* dataNode = dynamic_cast<BpTreeDataNode*>(pCur);
        
        // Iterate through all the data map and print book data
        for (auto& entry : *(dataNode->getDataMap())) {
            *fout << entry.second->getName() << "/" << entry.second->getCode() << "/"
                << entry.second->getAuthor() << "/" << entry.second->getYear() << "/"
                << entry.second->getLoanCount() << endl;
        }

        // move to next data node
        pCur = dataNode->getNext();
    }

    return true;
}

bool BpTree::Delete(LoanBookData* data) {
    return true;
}
