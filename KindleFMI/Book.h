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
	Book();

	void Save();
	//setters
	void setAuthor(const char* author);

	void setHeadline(const char* headline);

	void setRating(double rating);

	void setPagesCount(int pages_count);

	void setCommentsCount(int comments_count);

	void setPages(const Page* pages);

	void setComments(const char* const* comments);

	void AddRate(int rate, const char* username);

	void addPage(const char* page);

	void addComment(const char* comment, const char* author);
	//getters 
	const int getPagesCount();
	const int getCommentsCount();
	const Page getPage(int number);
	const char* const* getComments();
	const char* getAuthor();
	const char* getHeadline();
	const double getRating();
};