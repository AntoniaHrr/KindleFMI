#pragma once
#include "User.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <cstring>

//fourth

class Kindle {
private:
	User* users;
	int u=0;
	Book* books;
	int b=0;
	User* logged;
public:
	Kindle();

	Kindle& operator=(const Kindle& other);
	~Kindle();
	void free();
	void copyFrom(const Kindle& other);
	void UpdateBook(const char* title, const char* author, const char* content);
	void AddRate(const char* title, int rate);

	void AddComment(const char* title, const char* comment);

	void ViewComments(char* title);
	void ViewRating(char* title);

	void ReadPageFromBook(const char* title, int number);

	void ReadBook(const char* title);

	void WriteBook(const char* author, const char* title, const char* content);
	void SaveUsersandBooks();
	void ReadUsersandBooks();

	void Register(const char* name, const char* password);

	bool Login(const char* name, const char* password);

	void ViewContent();

	void Quit();

	

};
