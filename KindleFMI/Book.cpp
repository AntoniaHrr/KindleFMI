#include <iostream>
#include <cstring>
#include <fstream>
#include "Book.h"
#include "Page.h"
#include "Rates.h"

using namespace std;

Book::Book() {
	this->headline = nullptr;
	this->author = nullptr;
	this->rating = 0;
	this->comments = nullptr;
	this->pages_count = 0;
	this->comments_count = 0;
	this->pages = nullptr;
	this->r = nullptr;
	this->r_count = 0;
}


Book& Book::operator=(const Book& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
Book::~Book()
{
	free();
}
void Book::free() {
	delete[] headline;
	delete[] author;
	delete[] r;
	delete[] pages;
	for (int i = 0; i < comments_count; i++)
	{
		delete[] comments[i];
	}
	delete[] comments;
	
}
void Book::copyFrom(const Book& other) {

	int len = strlen(other.headline);
	this->headline = new char[len + 1];
	for (int i = 0; i < len + 1; i++) {
		this->headline[i] = other.headline[i];
	}

	int lenght = strlen(other.author);
	this->author = new char[lenght + 1];
	for (int i = 0; i < lenght + 1; i++) {
		this->author[i] = other.author[i];
	}

	this->r = new Rate[other.r_count];
	for (int i = 0; i < other.r_count; i++) {
		r[i] = other.r[i];
	}

	this->pages = new Page[other.pages_count];
	for (int i = 0; i < other.pages_count; i++) {
		pages[i] = other.pages[i];
	}

	this->rating = other.rating;
	this->r_count = other.r_count;
	this->comments_count = other.comments_count;
	this->pages_count = other.pages_count;

	this->comments = new char* [comments_count];
	for (int i = 0; i < comments_count; i++)
	{
		int len = strlen(other.comments[i]);
		this->comments[i] = new char[len + 1];
		for (int j = 0; j < len + 1; j++)
		{
			comments[i][j] = other.comments[i][j];
		}
	}
}

void Book::setRating(double rating) {
	this->rating = rating;
}

void Book::setPages(const Page* pages) {
	for (int i = 0; i < pages_count; i++)
	{
		this->pages[i] = pages[i];
	}
}

void Book::setComments(const char* const* comments) {
	for (int i = 0; i < comments_count; i++)
	{
		int len = strlen(comments[i]);
		strcpy_s(this->comments[i], len + 1, comments[i]);
	}
}

void Book::setPagesCount(int pages_count) {
	this->pages_count = pages_count;
}

void Book::setCommentsCount(int comments_count) {
	this->comments_count = comments_count;
}

void Book::setHeadline(const char* headline) {
	int lenght = strlen(headline);
	this->headline = new char[lenght + 1];
	for (int i = 0; i < lenght + 1; i++) {
		this->headline[i] = headline[i];
	}
}

void Book::setAuthor(const char* author) {
	int lenght = strlen(author);
	this->author = new char[lenght + 1];
	for (int i = 0; i < lenght + 1; i++) {
		this->author[i] = author[i];
	}
}

void Book::Read(ifstream& myfile) {
	int x = strlen(headline);
	int y = strlen(author);
	myfile.read(( char*)&x, sizeof(int));
	myfile.read((char*)headline, strlen(headline));
	myfile.read((char*)&y, sizeof(int));
	myfile.read((char*)author, strlen(author));
	myfile.read((char*)&rating, sizeof(rating));
	myfile.read((char*)&r_count, sizeof(int));

	for (int i = 0; i < r_count; i++)
	{
		r->Read(myfile);
	}

	myfile.read((char*)&pages_count, sizeof(int));
	for (int i = 0; i < pages_count; i++) {
		pages->Read(myfile);
	}

	myfile.read((char*)&comments_count, sizeof(int));
	for (int j = 0; j < comments_count; j++)
	{
		int z = strlen(comments[j]);
		myfile.read((char*)&z, sizeof(int));
		myfile.read((char*)comments[j], strlen(comments[j]));
	}

}

void Book::Save(ofstream& myfile) {
	int x = strlen(headline);
	int y = strlen(author);
	myfile.write((const char*)&x, sizeof(int));
	myfile.write((const char*)headline, strlen(headline));
	myfile.write((const char*)&y, sizeof(int));
	myfile.write((const char*)author, strlen(author));
	myfile.write((const char*)&rating, sizeof(rating));
	myfile.write((const char*)&r_count, sizeof(int));

	for (int i = 0; i < r_count; i++)
	{
		r->Save(myfile);
	}
	
	myfile.write((const char*)&pages_count, sizeof(int));
	for (int i = 0; i < pages_count; i++) {
		pages->Save(myfile);
	}

	myfile.write((const char*)&comments_count, sizeof(int));
	for (int j = 0; j < comments_count; j++)
	{
		int z = strlen(comments[j]);
		myfile.write((const char*)&z, sizeof(int));
		myfile.write((const char*)comments[j], strlen(comments[j]));
	}
	
	
}

void Book::AddRate(int rate, const char* username) {
	for (int i = 0; i < r_count; i++) {
		if (strcmp(r[i].getUsername(), username) == 0) {
			r[i].setTheRate(rate);
			return;
		}
	}
	r_count++;
	Rate* place_holder = new Rate[r_count];
	for (int i = 0; i < r_count - 1; i++)
	{
		place_holder[i] = r[i];
	}
	delete[] r;

	place_holder[r_count - 1] = Rate(rate, username);
	r = place_holder;
	//?
	rating = 0;
	for (int i = 0; i < r_count; i++) {
		rating = rating + r[i].getTheRate();
	}
	rating = rating / r_count;
}

void Book::addPage(const char* page) {
	pages_count++;
	Page* place_holder = new Page[pages_count];
	for (int i = 0; i < pages_count - 1; i++)
	{
		place_holder[i] = pages[i];
	}
	delete[] pages;

	place_holder[pages_count - 1].setNumber(pages_count);
	place_holder[pages_count - 1].setContent(page);
	this->pages = place_holder;
}

void Book::addComment(const char* comment, const char* author) {

	comments_count = comments_count + 2;
	char** place_holder = new char* [comments_count];
	for (int i = 0; i < comments_count - 2; i++)
	{
		place_holder[i] = comments[i];
	}
	delete[] comments;
	place_holder[comments_count - 2] = new char[strlen(author) + 1];
	for (int i = 0; i < strlen(author) + 1; i++)
	{
		place_holder[comments_count - 2][i] = author[i];
	}
	place_holder[comments_count - 1] = new char[strlen(comment) + 1];
	for (int i = 0; i < strlen(comment) + 1; i++)
	{
		place_holder[comments_count - 1][i] = comment[i];
	}
	this->comments = place_holder;
	delete[] place_holder;

}

const int Book::getPagesCount() {
	return pages_count;
}
const int Book::getCommentsCount() {
	return comments_count;
}
const Page Book::getPage(int number) {
	return pages[number];
}
const char* const* Book::getComments() {
	return comments;
}
const char* Book::getAuthor() {
	return author;
}
const char* Book::getHeadline() {
	return headline;
}
const double Book::getRating() {
	return rating;
}