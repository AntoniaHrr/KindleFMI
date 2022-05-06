#include <iostream>
#include <fstream>
#include "Page.h"
using namespace std;

Page::Page() {
    this->number = 0;
    this->content = nullptr;
}
Page::Page(const char* content, int number) {
    this->number = number;
    int lenght = strlen(content);
    this->content = new char[lenght + 1];
    for (int i = 0; i < lenght + 1; i++) {
        this->content[i] = content[i];
    }
}
Page& Page::operator=(const Page& other) {
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}
Page::~Page()
{
    free();
}
void Page::free() {
    delete[] content;
}
void Page::copyFrom(const Page& other) {

    int len = strlen(other.content);
    this->content = new char[len + 1];
    for (int i = 0; i < len + 1; i++) {
        this->content[i] = other.content[i];
    }
    this->number = other.number;
}

void Page::Save(ofstream& myfile) {
    int x = strlen(content);
    myfile.write((const char*)&number, sizeof(int));
    myfile.write((const char*)&x, sizeof(int));
    myfile.write((const char*)content, strlen(content));
}

//setters
void Page::setNumber(int number) {
    this->number = number;
}

void Page::setContent(const char* content) {
    int lenght = strlen(content);
    this->content = new char[lenght + 1];
    for (int i = 0; i < lenght + 1; i++) {
        this->content[i] = content[i];
    }
}