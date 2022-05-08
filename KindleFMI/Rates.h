#pragma once
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Rate {
private:
	int r;
	char* username;

public:
	Rate();
	void Save(ofstream& myfile);
	void Read(ifstream& myfile);
	Rate(int r, const char* username);
	Rate& operator=(const Rate& other);
	void free();
	void copyFrom(const Rate& other);
//setters
	void setTheRate(int r);
//getters
	const char* getUsername();
	const int getTheRate();
};