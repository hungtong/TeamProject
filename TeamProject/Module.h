/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class Module Declaration

#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

#ifndef MODULE_H
#define MODULE_H

class Module {

private:
	string name = "Module", description = "A Very General Module";

public:

	string getName();
	string getDescription();

	void setName(string name);
	void setDescription(string description);

	virtual void display() = 0;

	static void showMainMenu();
};

#endif // !MODULE_H
