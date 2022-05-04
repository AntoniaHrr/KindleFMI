#pragma once
#include "Book.h"
#include <fstream>

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
	void WriteBook(Book book) {
		w++;
		Book* place_holder = new Book[w];
		for (int i = 0; i < w - 1; i++)
		{
			place_holder[i] = written[i];
		}
		delete[] written;
		place_holder[w - 1].setAuthor(book.getAuthor());
		place_holder[w - 1].setHeadline(book.getHeadline());
		place_holder[w - 1].setComments(book.getComments()); //??????
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
	void Save() {
		int x = strlen(username);
		int y = strlen(password);
		ofstream myfile("UsersInfo.bin", ios::binary | ios::app);
		if (!myfile.is_open())
		{
			return;
		}
			myfile.write((const char*)&x, sizeof(int));
			myfile.write((const char*)username, strlen(username));
			myfile.write((const char*)&y, sizeof(int));
			myfile.write((const char*)password, strlen(password));
			myfile.write((const char*)&r, sizeof(r));
			myfile.write((const char*)read, sizeof(Book) * r);
			myfile.write((const char*)&w, sizeof(w));
			myfile.write((const char*)written, sizeof(Book) * w);
			myfile.close();
			
	}

	bool hasRead(const char* title) {
		for (int i = 0; i < r; i++)
		{
			if (strcmp(read[i].getHeadline(), title) == 0)
			{
				return true;
			}
		}
		return false;
	}

	void ReadComments(Book book) {
		for (int i = 0; i < book.getCommentsCount(); i=i+2)
		{
			cout << book.getComments()[i];
			cout << book.getComments()[i + 1];
			cout << endl;
		}
	}
	void ReadBook(Book book) {
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
	void WriteComment(Book book,const char* comment) {
		for (int i = 0; i < r; i++)
		{
			if(Equal(book.getHeadline(), read[i].getHeadline()))
			{
				book.addComment(comment, username);
				return;
			}
		}
	}
	void ReadPage(Book book, int number) {
		if (number > book.getPagesCount()) {
			return;
		}
		cout << book.getPage(number);
	}
	void ChangeBook(Book book, char* page) {
		book.addPage(page);
	}
	//setters
	void setUsername(const char* username) {
		int lenght = strlen(username);
		this->username = new char[lenght + 1];
		for (int i = 0; i < lenght + 1; i++) {
			this->username[i] = username[i];
		}
	}
	void setPassword(const char* password) {
		int lenght = strlen(password);
		this->password = new char[lenght + 1];
		for (int i = 0; i < lenght + 1; i++) {
			this->password[i] = password[i];
		}
	}
	//getters
	const char* getName() {
		return username;
	}
	const char* getPassword() {
		return password;
	}

	bool Equal(const char* task, const char* TaskOne)
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

};
