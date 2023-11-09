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
        fin >> cmd;

        if (cmd == "LOAD") {
            if (LOAD()) {
                printSuccessCode();
            }
            else {
                flog << "failed" << endl;
            }
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
        //if (iss >> name >> code >> author >> year >> loan_count) {

            LoanBookData* newBook = new LoanBookData;
            newBook->setBookData(name, stoi(code), author, stoi(year));
            
            

            if (!bptree->Insert(newBook)) {
                printErrorCode(100);
                return false;
            }
            



        
       // else {
       //         flog << "ÆÄ½Ì ¿À·ù" << endl;
       //     }
        }
        inputFile.close();

        
        return true;

    

    }


bool Manager::ADD()
{

	return true;
}

bool Manager::SEARCH_BP_BOOK(string book)
{
    return true;
}

bool Manager::SEARCH_BP_RANGE(string s, string e)
{
    return true;
}

bool Manager::PRINT_BP()
{
    return true;
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

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
    flog << "=======================" << endl;
    flog << "Success" << endl;
    flog << "=======================" << endl << endl;
}