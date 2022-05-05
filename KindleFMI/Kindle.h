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
	Kindle() {
		this->users = NULL;
		this->u = 0;
		this->b = 0;
		this->logged = nullptr;
		this->books = nullptr;
	}

	Kindle& operator=(const Kindle& other) {
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}
	~Kindle()
	{
		free();
	}
	void free() {
		delete[] users;
		delete[] books;
		delete[] logged;
	}
	void copyFrom(const Kindle& other) {
		for (int i = 0; i < u; i++) {
			this->users[i] = other.users[i];
		}
		for (int i = 0; i < b; i++) {
			this->books[i] = other.books[i];
		}
		this->b = other.b;
		this->u = other.u;
	}

	//////////////////////////////////////////////
	void UpdateBook(Book book, const char* content) {
		book.addPage(content);
	}
	/////////////////////////////////////////////
	void AddRate(const char* title, int rate) {
		for (int i = 0; i < b; i++) {
			if (strcmp(title, books[i].getHeadline()) == 0)
			{
				if (logged->hasRead(title))
				{
				books[i].AddRate(rate, logged->getName());
				}	
			}
		}
	}

	void Write(char* author, char* title, char* content) {
		Book book;
		book.setAuthor(author);
		book.setHeadline(title);
		book.addPage(content); 

		b++;
		Book* place_holder = new Book[b];
		for (int i = 0; i < b - 1; i++)
		{
			place_holder[i] = books[i];
		}
		delete[] books;
		place_holder[b - 1].setAuthor(book.getAuthor());
		place_holder[b - 1].setHeadline(book.getHeadline());
		place_holder[b - 1].setPagesCount(book.getPagesCount());

		Page* place_holderPages = new Page[book.getPagesCount()];
		for (int i = 0; i < book.getPagesCount(); i++)
		{
			place_holderPages[i] = book.getPage(i);
		}
		place_holder[b - 1].setPages(place_holderPages);


		this->books = place_holder;
		delete[] place_holder;


		for (int i = 0; i < u; i++)
		{
			if (strcmp(users[i].getName(), author) == 0)
			{
				users[i].WriteBook(book);
				return;
			}

		}

	}
	void SaveUsersandBooks() {
		ofstream myfileUsers("UsersInfo.bin", ios::binary);
		if (!myfileUsers.is_open())
		{
			return;
		}
		for (int i = 0; i < u; i++) {
			users[i].Save();
		}
		myfileUsers.close();

		ofstream myfile("BooksInfo.bin", ios::binary); 
		if (!myfile.is_open())
		{
			return;
		}
		for (int i = 0; i < b; i++)
		{
			books[i].Save();
		}
		myfile.close();
	}

	void Register(const char* name,const char* password) {
		for (int i = 0; i < u ; i++)
		{
			if (strcmp(users[i].getName(), name) == 0)
			{
				cout << "Username is taken!";
				return;
			}
		}
		u++;
			User* place_holder = new User[u];
			for (int i = 0; i < u - 1; i++)
			{
				place_holder[i] = users[i];
			delete[] this->users;
			}
			place_holder[u - 1].setUsername(name);
			place_holder[u - 1].setPassword(password);
			
			for (int i = 0; i < u; i++)
			{
			this->users[i] = place_holder[i];
			}
			
			
			delete[] place_holder;
	
		
	}

	bool Login(const char* name,const char* password) {
		for (int i = 0; i < u; i++)
		{
			if (strcmp(users[i].getName(), name) == 0 && strcmp(users[i].getPassword(), password) == 0)
			{
				logged = new User(users[i]);
				return 1;
			}
				
		}
		return 0;
	}

	void ViewContent() {
		for (int i = 0; i < b; i++)
		{
			cout << books[i].getHeadline() << " by " << books[i].getAuthor() << endl;
		}
	}

	void Quit() {
		SaveUsersandBooks();
		delete[] logged;
		logged = nullptr;
	}

	const char* getUsername(){
		return users[1].getName();
	}


};
