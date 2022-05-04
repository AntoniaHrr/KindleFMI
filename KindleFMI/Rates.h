#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class Rate {
private:
	int r;
	char* username;

public:
	Rate() {
		this->r = 0;
		this->username = nullptr;
	}
	Rate(int r, const char* username) {
		this->r = r;
		int len = strlen(username);
		strcpy_s(this->username, len + 1, username);
	}
	void setTheRate(int r) {
		this->r = r;
	}
	Rate& operator=(const Rate& other) {
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}
	void free() {
		delete[] username;
	}
	void copyFrom(const Rate& other) {

		int len = strlen(other.username);
		this->username = new char[len + 1];
		for (int i = 0; i < len + 1; i++) {
			this->username[i] = other.username[i];
		}
		this->r = other.r;
	}

	const char* getUsername() {
		return username;
	}
	const int getTheRate() {
		return r;
	}
};