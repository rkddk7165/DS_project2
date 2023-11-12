#include "Manager.h"

LoanBookData loanBookData;


     

void Manager::run(const char* command)
{
    
	fin.open(command);
	if (!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
    //open log.txt for writing output
    flog.open("log.txt");

    while (!fin.eof())
    {
        string cmd;
        if (!getline(fin, cmd))
        {
            break;
        }

        else if (cmd == "LOAD") {
            if (LOAD()) {
                printSuccessCode("LOAD");
            }
            else {
                flog << "failed" << endl;
            }
        }

        else if (cmd.substr(0, 3) == "ADD") {
            string addData = cmd.substr(4);

            ADD(addData);

        }

        else if (cmd.substr(0, 9) == "SEARCH_BP") {
            string bookName = cmd.substr(10);

            bool found = bptree->searchBook(bookName);

            if (!found) {
                flog << "Book not found." << endl;
            }
        }
        else if (cmd == "PRINT_BP") {
            bptree->printBook();
        }

        else {
            flog << "unknowned" << endl;
        }
    }

            fin.close();
            flog.close();
            return;
        
    
}

bool Manager::LOAD()
{
    // Read data.txt and store datas in LoanBookData
    ifstream inputFile("loan_book.txt");
    if (!inputFile.is_open()) {
        printErrorCode(100);
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string tmp;
        
        string name, author;
        string code, year, loan_count;

        getline(iss, name, '\t');
        getline(iss, code, '\t');
        getline(iss, author, '\t');
        getline(iss, year, '\t');
        getline(iss, loan_count, '\t');

            LoanBookData* newBook = new LoanBookData;
            newBook->setBookData(name, stoi(code), author, stoi(year));

            for (int i = 0; i < stoi(loan_count); i++) {
                newBook->updateCount();
            }
            
            if (!bptree->Insert(newBook)) {
                printErrorCode(100);
                return false;
            }
        }
        inputFile.close();
        return true;
    }


bool Manager::ADD(string addData)
{
    istringstream iss(addData);
    string tmp;

    string name, author, code, year;

    getline(iss, name, '\t');
    getline(iss, code, '\t');
    getline(iss, author, '\t');
    getline(iss, year, '\t');

    LoanBookData* newBook = new LoanBookData;
    newBook->setBookData(name, stoi(code), author, stoi(year));

    if (!bptree->Insert(newBook)) {
        printErrorCode(200);
        return false;

    }
    else {
        flog << "========ADD========" << endl << name << "/" << code << "/" << author << "/" << year << endl << "====================" << endl;

        return true;
    }



	
}

bool Manager::SEARCH_BP_BOOK(string book)
{
    if (bptree) {
        if (bptree->searchBook(book)) {
            return true;
        }
        else {
            printErrorCode(200);
        }
    }
    else {
        printErrorCode(200);
    }
    return false;
}

bool Manager::SEARCH_BP_RANGE(string s, string e)
{
    return true;
}

bool Manager::PRINT_BP() {
    if (bptree) {
        if (bptree->printBook()) {
            printSuccessCode("PRINT_BP");
            return true;
        }
        else {
            printErrorCode(300);
        }
    }
    else {
        printErrorCode(300);
    }

    return false;
}

bool Manager::PRINT_ST()
{
    return true;
}

bool Manager::DELETE()
{
    return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
    flog << "=======================" << endl;
    flog << "ERROR " << n << endl;
    flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode(string command) {//SUCCESS CODE PRINT 
    flog << "========="<< command << "========" << endl;
    flog << "Success" << endl;
    flog << "=======================" << endl << endl;
}