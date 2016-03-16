/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class Module Specification

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Module.h"
#include "CashierModule.h"
#include "InventoryModule.h"
#include "ReportModule.h"
#include "Utils.h"

string Module::getName() {
	return name;
}

string Module::getDescription() {
	return description;
}

void Module::setName(string name) {
	this->name = name;
}

void Module::setDescription(string description) {
	this->description = description;
}

void Module::showMainMenu() {
	system("CLS");
	cout << "\t\t  Serendipity Booksellers" << endl;
	cout << "\t\t\t Main Menu" << endl << endl;
	cout << "\t\t 1. Cashier Module" << endl;
	cout << "\t\t 2. Inventory Database Module" << endl;
	cout << "\t\t 3. Report Module" << endl;
	cout << "\t\t 4. Exit" << endl << endl;

	switch (Utils::showChoices(1,4)) {
	case 1:
		CashierModule::getInstance()->display();
		showMainMenu();
		break;
	case 2:
		InventoryModule::getInstance()->display();
		showMainMenu();
		break;
	case 3:
		ReportModule::getInstance()->display();
		showMainMenu();
	case 4:
		cout << "Thank You For Using Serendipity Booksellers!" << endl << endl;
	}
}


