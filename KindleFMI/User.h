#pragma once
#include "Book.h"
#include <fstream>
#include <cstring>
#pragma warning(disable: 4996)

using namespace std;

class User {
private:
	char* username;
	char* password;
	Book* read;
	Book* written;
	int r;
	int w;
public:

	User();
	User& operator=(const User& other);
	~User();
	void free();
	void copyFrom(const User& other);
	void WriteBook(Book book);
	void Save(ofstream& myfile);
	void Read(ifstream& myfile);
	bool hasRead(const char* title);
	void ReadComments(Book book);
	void ReadBook(Book book);
	void WriteComment(Book book, const char* comment);
	void ReadPage(Book book, int number);
	void ChangeBook(Book book, char* page);
	//setters
	void setUsername(const char* username);
	void setPassword(const char* password);
	//getters
	const char* getName();
	const char* getPassword();

	bool Equal(const char* task, const char* TaskOne);

};
