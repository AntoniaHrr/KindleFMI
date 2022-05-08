#include "User.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "Kindle.h"

using namespace std;

Kindle::Kindle() {
	this->users = nullptr;
	this->u = 0;
	this->b = 0;
	this->logged = nullptr;
	this->books = nullptr;
	//readfrom
}

Kindle& Kindle::operator=(const Kindle& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
Kindle::~Kindle()
{
	free();
}
void Kindle::free() {
	delete[] users;
	delete[] books;
	delete logged;
}
void Kindle::copyFrom(const Kindle& other) {

	users = new User[other.u];
	for (int i = 0; i < other.u; i++) {
		this->users[i] = other.users[i];
	}
	books = new Book[other.b];
	for (int i = 0; i < other.b; i++) {
		this->books[i] = other.books[i];
	}
	logged = new User(*other.logged);

	this->b = other.b;
	this->u = other.u;
}

//////////////////////////////////////////////
void Kindle::UpdateBook(const char* title, const char* author, const char* content) {
	for (int i = 0; i < b; i++)
	{
		if (strcmp(books[i].getHeadline(), title) == 0 && strcmp(books[i].getAuthor(), author) == 0)
		{
			books[i].addPage(content);
		}
	}

}
/////////////////////////////////////////////
void Kindle::AddRate(const char* title, int rate) {
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

void Kindle::AddComment(const char* title, const char* comment) {
	for (int i = 0; i < b; i++) {
		if (strcmp(title, books[i].getHeadline()) == 0)
		{
			if (logged->hasRead(title))
			{
				books[i].addComment(comment, logged->getName());
			}
		}
	}
}

void Kindle::ViewComments(char* title) {
	for (int i = 0; i < b; i++) {
		if (strcmp(title, books[i].getHeadline()) == 0)
		{
			for (int j = 0; j < books[i].getCommentsCount(); j++)
			{
				cout << books[i].getComments()[j] << endl;
			}

		}
	}
}

void Kindle::ReadPageFromBook(const char* title, int number) {
	for (int i = 0; i < b; i++) {
		if (strcmp(title, books[i].getHeadline()) == 0) {

			cout << books[i].getPage(number) << endl;

		}
	}
}

void Kindle::ReadBook(const char* title) {
	for (int i = 0; i < b; i++) {
		if (strcmp(title, books[i].getHeadline()) == 0) {
			for (int j = 0; j < books[i].getPagesCount(); j++)
			{
				cout << books[i].getPage(j) << endl;
			}

		}
	}
}

void Kindle::WriteBook(const char* author, const char* title, const char* content) {
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


	for (int i = 0; i < u; i++)
	{
		if (strcmp(users[i].getName(), author) == 0)
		{
			users[i].WriteBook(book);
			return;
		}

	}

}
void Kindle::SaveUsersandBooks() {
	ofstream myfileUsers("UsersInfo.bin", ios::binary);
	if (!myfileUsers.is_open())
	{
		return;
	}
	for (int i = 0; i < u; i++) {
		users[i].Save(myfileUsers);
	}
	myfileUsers.close();

	ofstream myfileBooks("BooksInfo.bin", ios::binary);
	if (!myfileBooks.is_open())
	{
		return;
	}
	for (int i = 0; i < b; i++)
	{
		books[i].Save(myfileBooks);
	}
	myfileBooks.close();
}

void Kindle::Register(const char* name, const char* password) {
	for (int i = 0; i < u; i++)
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
	}
	delete[] this->users;

	place_holder[u - 1].setUsername(name);
	place_holder[u - 1].setPassword(password);


	this->users = place_holder;


}

bool Kindle::Login(const char* name, const char* password) {
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

void Kindle::ViewContent() {
	for (int i = 0; i < b; i++)
	{
		cout << books[i].getHeadline() << " by " << books[i].getAuthor() << endl;
	}
}

void Kindle::Quit() {
	SaveUsersandBooks();
	delete[] logged;
	logged = nullptr;
}