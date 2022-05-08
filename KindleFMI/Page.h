#pragma once
#include <iostream>
#include <fstream>
using namespace std;

//fourth is done

class Page {
private:
	char* content;
    int number;
public:
    Page();
    Page(const char* content, int number);
    Page& operator=(const Page& other);
    ~Page();
    void free();
    void copyFrom(const Page& other);
    void Save(ofstream& myfile);
    void Read(ifstream& myfile);

    //setters
    void setNumber(int number);

    void setContent(const char* content);

    friend ostream& operator<<(ostream& out, const Page& page) {
        return out << page.content << std::endl;
    }

};
