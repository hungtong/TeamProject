// Class CashierModule Specification

#include "stdafx.h"
#include<time.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Module.h"
#include "CashierModule.h"
#include "Utils.h"

using namespace std;

CashierModule * CashierModule::cashierModule;
int CashierModule::numberItems = 0;
string CashierModule::purchaseBooks[1024];

CashierModule::CashierModule() {
	setName("Cashier Module");
	setDescription("act as a cash register");
	_strdate_s(datePurchase);
}

char * CashierModule::getDatePurchase() {
	return datePurchase;
}

CashierModule * CashierModule::getInstance() {
	if (cashierModule == NULL) {
		cashierModule = new CashierModule();
	}
	return cashierModule;
}

/* 
clears the screen
if there are 0 items, displays the information to access different modules
else, shows the current items in cart
gives options to checkout, delete items, or go back to menu

*/ 
void CashierModule::display() {
	system("CLS");
	cout << "Serendipity Book Sellers" << endl << endl;
	cout << "Date: " << datePurchase << endl << endl;
	if (numberItems == 0) {
		cout << "\t You Currently Have No Book In Cart" << endl;
		cout << "\t Access Report Module To See A List Of Available Books" << endl;
		cout << "\t Access Inventory Module To Look Up And Add Books To Cart" << endl;
		system("pause");
	}
	else {
		cout << "\t\t Items In Cart" << endl << endl;
		for (int i = 0; i < numberItems; i++) 
			cout << purchaseBooks[i] << endl;

		cout << "\t\t 1. Checkout" << endl;
		cout << "\t\t 2. Delete Items In Cart" << endl;
		cout << "\t\t 3. Back To Main Menu" << endl << endl;
		
		switch (Utils::showChoices(1,3)) {
		case 1:
			
		case 2:
			cout << "Enter Item Number: ";
			int number;
			cin >> number;
			break;
		}
	}
	Module::showMainMenu();	
	cout << "\t\t Subtotal:    " << endl;
	cout << "\t\t Tax:         " << endl;
	cout << "\t\t Total:       " << endl;
}
