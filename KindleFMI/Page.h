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
    Page(const Page& other);
    Page(const char* content, int number);
    Page& operator=(const Page& other);
    ~Page();
    void free();
    void copyFrom(const Page& other);
    void Save(ofstream& myfile);
    void Read(ifstream& myfile);

   const char* getContent() const {
        return content;
    }

    //setters
    void setNumber(int number);

    void setContent(const char* content);


};
