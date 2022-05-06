#include <iostream>
#include <cstring>
#include <fstream>
#include "Rates.h"

using namespace std;

Rate::Rate() {
	this->r = 0;
	this->username = nullptr;
}
Rate::Rate(int r, const char* username) {
	this->r = r;
	int len = strlen(username);
	strcpy_s(this->username, len + 1, username);
}
Rate& Rate::operator=(const Rate& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
void Rate::free() {
	delete[] username;
}
void Rate::copyFrom(const Rate& other) {

	int len = strlen(other.username);
	this->username = new char[len + 1];
	for (int i = 0; i < len + 1; i++) {
		this->username[i] = other.username[i];
	}
	this->r = other.r;
}
//setters
void Rate::setTheRate(int r) {
	this->r = r;
}
//getters
const char* Rate::getUsername() {
	return username;
}
const int Rate::getTheRate() {
	return r;
}

void Rate::Save(ofstream& myfile) {
	int x = strlen(username);
	myfile.write((const char*)&r, sizeof(int));
	myfile.write((const char*)&x, sizeof(int));
	myfile.write((const char*)username, strlen(username));
}