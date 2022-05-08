#include "Book.h"
#include "User.h"
#include <fstream>
#include <cstring>
#pragma warning(disable: 4996)

using namespace std;


User::User() {
	this->username = nullptr;
	this->password = nullptr;
	this->read = nullptr;
	this->written = nullptr;
	this->r = 0;
	this->w = 0;
}
User& User::operator=(const User& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
User::~User()
{
	free();
}
void User::free() {
	delete[] username;
	delete[] password;
	delete[] read;
	delete[] written;
}

void User::copyFrom(const User& other) {

	int len = strlen(other.username);
	this->username = new char[len + 1];
	strcpy(this->username, other.username);

	int lenght = strlen(other.password);
	this->password = new char[lenght + 1];
	strcpy(this->password, other.password);

	this->written = new Book[other.w];
	for (int i = 0; i < other.w; i++) {
		written[i] = other.written[i];
	}

	this->read = new Book[other.r];
	for (int i = 0; i < other.r; i++) {
		read[i] = other.read[i];
	}
}


void User::WriteBook(Book book) {
	w++;
	Book* place_holder = new Book[w];
	for (int i = 0; i < w - 1; i++)
	{
		place_holder[i] = written[i];
	}
	delete[] written;
	place_holder[w - 1].setAuthor(book.getAuthor());
	place_holder[w - 1].setHeadline(book.getHeadline());
	place_holder[w - 1].setComments(book.getComments());
	place_holder[w - 1].setPagesCount(book.getPagesCount());
	place_holder[w - 1].setCommentsCount(book.getCommentsCount());
	place_holder[w - 1].setRating(book.getRating());

	Page* place_holderPages = new Page[book.getPagesCount()];
	for (int i = 0; i < book.getPagesCount(); i++)
	{
		place_holderPages[i] = book.getPage(i);
	}
	place_holder[w - 1].setPages(place_holderPages);

	this->written = place_holder;
}
void User::Save(ofstream& myfile) {
	int x = strlen(username);
	int y = strlen(password);

	myfile.write((const char*)&x, sizeof(int));
	myfile.write((const char*)username, strlen(username));
	myfile.write((const char*)&y, sizeof(int));
	myfile.write((const char*)password, strlen(password));

	myfile.write((const char*)&r, sizeof(r));
	for (int i = 0; i < r; i++) {
		read->Save(myfile);
	}
	myfile.write((const char*)&w, sizeof(w));
	for (int i = 0; i < w; i++) {
		written->Save(myfile);
	}

}

void User::Read(ifstream& myfile) {
	int x = strlen(username);
	int y = strlen(password);

		myfile.read((char*)&x, sizeof(int));
		myfile.read((char*)username, strlen(username));
		myfile.read((char*)&y, sizeof(int));
		myfile.read((char*)password, strlen(password));

		myfile.read((char*)&r, sizeof(r));
	for (int i = 0; i < r; i++) {
		read->Read(myfile);
	}
		myfile.read((char*)&w, sizeof(w));
	for (int i = 0; i < w; i++) {
		written->Read(myfile);
	}

	
}

bool User::hasRead(const char* title) {
	for (int i = 0; i < r; i++)
	{ //check for author too
		if (strcmp(read[i].getHeadline(), title) == 0)
		{
			return true;
		}
	}
	return false;
}

void User::ReadComments(Book book) {
	for (int i = 0; i < book.getCommentsCount(); i = i + 2)
	{
		cout << book.getComments()[i];
		cout << book.getComments()[i + 1];
		cout << endl;
	}
}
void User::ReadBook(Book book) {
	//check if already is read before adding to read*
	for (int i = 0; i < book.getPagesCount(); i++)
	{
		cout << book.getPage(i);
		cout << endl;
	}
	r++;
	Book* place_holder = new Book[r];
	for (int i = 0; i < r - 1; i++)
	{
		place_holder[i] = read[i];
	}
	delete[] read;
	place_holder[r - 1].setAuthor(book.getAuthor());
	place_holder[r - 1].setHeadline(book.getHeadline());
	place_holder[r - 1].setComments(book.getComments());
	place_holder[r - 1].setPagesCount(book.getPagesCount());
	place_holder[r - 1].setCommentsCount(book.getCommentsCount());
	place_holder[r - 1].setRating(book.getRating());

	Page* place_holderPages = new Page[book.getPagesCount()];
	for (int i = 0; i < book.getPagesCount(); i++)
	{
		place_holderPages[i] = book.getPage(i);
	}
	place_holder[r - 1].setPages(place_holderPages);

	this->read = place_holder;
}
void User::WriteComment(Book book, const char* comment) {
	for (int i = 0; i < r; i++)
	{
		if (Equal(book.getHeadline(), read[i].getHeadline()))
		{
			book.addComment(comment, username);
			return;
		}
	}
}
void User::ReadPage(Book book, int number) {
	if (number > book.getPagesCount()) {
		return;
	}
	cout << book.getPage(number);
}
void User::ChangeBook(Book book, char* page) {
	//add check if in w
	book.addPage(page);
}
//setters
void User::setUsername(const char* username) {
	if (this->username != nullptr)
	{
		delete[] this->username;
	}
	int length = strlen(username);
	this->username = new char[length + 1]; //+ 1 for '\0'
	strcpy(this->username, username);
}
void User::setPassword(const char* password) {
	if (this->password != nullptr)
	{
		delete[] this->password;
	}
	int length = strlen(password);
	this->password = new char[length + 1]; //+ 1 for '\0'
	strcpy(this->password, password);
}
//getters
const char* User::getName() {
	return this->username;
}
const char* User::getPassword() {
	return this->password;
}

bool User::Equal(const char* task, const char* TaskOne)
{
	int count = 0;
	int i = 0;
	int j = 0;
	while (TaskOne[j] != '\0')
	{
		j++;
	}
	while (task[i] != '\0')
	{
		if (task[i] == TaskOne[i])
		{
			count++;
		}
		i++;
	}
	if (i > j || i == j) {
		if (i == count)
		{
			return true;
		}
		else return false;
	}
	else if (j > i) {
		if (j == count)
		{
			return true;
		}
		else return false;
	}
}
