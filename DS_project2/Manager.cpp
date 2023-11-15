#include "Manager.h"



//A function that reads a command from a command file and calls a function that performs the operation of that command.
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
                printErrorCode(100);
            }
        }

        else if (cmd.substr(0, 3) == "ADD") {
            string addData = cmd.substr(4);

            if (!ADD(addData)) {
                printErrorCode(200);
            }

        }
        

        //When reading the SEARCH_BP command
        else if (cmd.substr(0, 9) == "SEARCH_BP") {
            string args = cmd.substr(10);
            size_t spaceIndex = args.find('\t');

            if (spaceIndex != string::npos) {
                // If there are two SEARCH_BP arguments
                string start = args.substr(0, spaceIndex);
                string end = args.substr(spaceIndex + 1);

                SEARCH_BP_RANGE(start, end);
                   
            }
            else {
                // If SEARCH_BP has one argument
                string bookName = args;

                bool found = bptree->searchBook(bookName);

                if (!found) {
                    printErrorCode(300);
                }
            }
        }
        
        else if (cmd == "PRINT_BP") {
            PRINT_BP();
        }

        else if (cmd == "EXIT")
        {
            printSuccessCode("EXIT");
            break;
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
    // Read data.txt and store datas in LoanBookData instances and insert datas into BpTree
    ifstream inputFile("loan_book.txt");
    if (!inputFile.is_open()) {
        printErrorCode(100); //LOAD Error code
        return false;
    }

    string line;

    // Split a string based on tab (\t)
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
            
            //
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
        flog << "========ADD========" << endl << name << "/" << code << "/" << author << "/" << year << endl << "====================" << endl << endl;

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
        return false;
    }
    
}

bool Manager::SEARCH_BP_RANGE(string s, string e)
{
    if (bptree) {
        flog << "========SEARCH_BP========" << endl;

        if (bptree->searchRange(s, e)) {
            flog << "=========================" << endl << endl;
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

bool Manager::PRINT_BP() {
    if (bptree) {
        flog << "========PRINT_BP========" << endl;
        if (bptree->printBook()) {
            flog << "========================" << endl << endl;
            return true;
        }
        else {
            printErrorCode(400);
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