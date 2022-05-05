#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include "Page.h"
#include "Rates.h"

using namespace std;


class Book {
private:
	char* headline;
	char* author;
	double rating;
	Rate* r;
	int r_count;
	Page* pages;
	char** comments;
	int pages_count;
	int comments_count;
public:
	Book() { //yes
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




	void Save() {
		int x = strlen(headline);
		int y = strlen(author);
		ofstream myfile("BooksInfo.bin", ios::binary | ios::app);
		if (!myfile.is_open())
		{
			return;
		}
		myfile.write((const char*)&x, sizeof(int));
		myfile.write((const char*)headline, strlen(headline));
		myfile.write((const char*)&y, sizeof(int));
		myfile.write((const char*)author, strlen(author));
		myfile.write((const char*)&rating, sizeof(rating));
		myfile.write((const char*)&r, sizeof(r));
		myfile.write((const char*)&pages_count, sizeof(int));
		myfile.write((const char*)pages, sizeof(Page) * pages_count);
		myfile.write((const char*)&comments_count, sizeof(int));
		myfile.write((const char*)comments, sizeof(comments) * comments_count); //???
		myfile.close();

	}
	//setters
	void setAuthor(const char* author) {
		int lenght = strlen(author);
		this->author = new char[lenght + 1];
		for (int i = 0; i < lenght + 1; i++) {
			this->author[i] = author[i];
		}
	}
	void setHeadline(const char* headline) {
		int lenght = strlen(headline);
		this->headline = new char[lenght + 1];
		for (int i = 0; i < lenght + 1; i++) {
			this->headline[i] = headline[i];
		}
	}
	void setRating(double rating) {
		this->rating = rating;
	}
	void setPagesCount(int pages_count) {
		this->pages_count = pages_count;
	}
	void setCommentsCount(int comments_count) {
		this->comments_count = comments_count;
	}
	void setPages(const Page* pages) {
		for (int i = 0; i < pages_count; i++)
		{
			this->pages[i] = pages[i];
		}
	}
	void setComments(const char* const* comments) {
		for (int i = 0; i < comments_count; i++)
		{
			int len = strlen(comments[i]);
			strcpy_s(this->comments[i], len+1, comments[i]);
		}
	}

	void AddRate(int rate, const char* username) {
		for (int i = 0; i < r_count; i++) {
			if (strcmp(r[i].getUsername(), username)==0) {
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
		delete[] place_holder;

		rating = 0;
		for (int i = 0; i < r_count; i++) {
			rating = rating + r[i].getTheRate();
		}
		rating = rating / r_count;
	}

	void addPage(const char* page) {
		pages_count++;
		Page* place_holder = new Page[pages_count];
		for (int i = 0; i < pages_count - 1; i++)
		{
			place_holder[i] = pages[i];
		}
		delete[] pages;

		place_holder[pages_count-1].setNumber(pages_count);
		place_holder[pages_count-1].setContent(page);
		this->pages = place_holder;
		delete[] place_holder;
	}
	void addComment(const char* comment, const char* author) {

		comments_count=comments_count + 2;
		char** place_holder = new char*[comments_count];
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
	//getters 
	const int getPagesCount() {
		return pages_count;
	}
	const int getCommentsCount() {
		return comments_count;
	}
	const Page getPage(int number) {
		return pages[number];
	}
	const char* const* getComments() {
		return comments;
	}
	const char* getAuthor() {
		return author;
	}
	const char* getHeadline() {
		return headline;
	}
	const double getRating() {
		return rating;
	}


};