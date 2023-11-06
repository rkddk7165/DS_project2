#include "Manager.h"

LoanBookData loanBookData;
BpTree bptree;
     

void Manager::run(const char* command)
{
	fin.open(command);
	if (!fin)
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{

        // Read data.txt and store datas in MemberQueue
        ifstream inputFile("loan_book.txt");
        if (!inputFile.is_open()) {
            return;
        }
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string name, author;
            int code, year, loan_count;

            if (iss >> name >> code >> author >> year >> loan_count) {
                
                loanBookData.setBookData(name, code, author, year);
                
                
            }
            else {
                flog << "ÆÄ½Ì ¿À·ù" << endl;
            }
        }
        inputFile.close();

        // Open command.txt to read the commands
        // Open log.txt, the file to output the results
        fin.open(command);
        flog.open("log.txt");
       
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	
}

bool Manager::ADD()
{

	return true;
}