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
    Page() {
        this->number = 0;
        this->content = nullptr;
    }
    Page(const char* content, int number) {
        this->number = number;
        int lenght = strlen(content);
        this->content = new char[lenght + 1];
        for (int i = 0; i < lenght + 1; i++) {
            this->content[i] = content[i];
        }
    }
    Page& operator=(const Page& other) {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }

        return *this;
    }
    ~Page()
    {
        free();
    }
    void free() {
        delete[] content;
    }
    void copyFrom(const Page& other) {

        int len = strlen(other.content);
        this->content = new char[len + 1];
        for (int i = 0; i < len + 1; i++) {
            this->content[i] = other.content[i];
        }
        this->number = other.number;
    }

    //setters
    void setNumber(int number) {
        this->number = number;
    }

    void setContent(const char* content) {
        int lenght = strlen(content);
        this->content = new char[lenght + 1];
        for (int i = 0; i < lenght + 1; i++) {
            this->content[i] = content[i];
        }
    }

    friend ostream& operator<<(ostream& out, const Page& page) {
        return out << page.content << std::endl;
    }

};
