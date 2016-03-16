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

//get and define variables
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

void Module::showMainMenu() {//display main menu
	system("CLS");
	cout << "\t\t  Serendipity Booksellers" << endl;
	cout << "\t\t\t Main Menu" << endl << endl;//give user options 1-4
	cout << "\t\t 1. Cashier Module" << endl;
	cout << "\t\t 2. Inventory Database Module" << endl;
	cout << "\t\t 3. Report Module" << endl;
	cout << "\t\t 4. Exit" << endl << endl;

	switch (Utils::showChoices(1,4)) {//have user enter number 1-4
	case 1:
		CashierModule::getInstance()->display();//if 1: get instance then run cashier menu
		showMainMenu();
		break;
	case 2:
		InventoryModule::getInstance()->display();// if 2: get instance then run inventory menu
		showMainMenu();
		break;
	case 3:
		ReportModule::getInstance()->display();// if 3: get instance then run report menu
		showMainMenu();
	case 4:
		cout << "Thank You For Using Serendipity Booksellers!" << endl << endl;// if 4: say thanks then close
	}
}


