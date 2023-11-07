#pragma once

#include<iostream>
#include<cstring>
#include<string>

using namespace std;
//이 클래스는 객체 생성을 통해 하나의 책 데이터를 쪼개서 저장하는 클래스임
class LoanBookData
{
private:
    string name;
    int code;
    string author;
    int year;
    int loan_count;

public:
    LoanBookData() { this->loan_count = 0; }
    ~LoanBookData() {};

    // Overload the less than operator to compare LoanBookData objects.
    bool operator<(const LoanBookData& other) const {
        return this->name < other.name;
    }

    void setBookData(string name, int code, string author, int year) {
        this->name = name;
        this->code = code;
            this->author = author;
        this->year = year;
    }

    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    void updateCount() { this->loan_count += 1; }

    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
};
