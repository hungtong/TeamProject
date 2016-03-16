// Class CashierModule Specification

#include "stdafx.h"
#include<time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>

#include "Module.h"
#include "CashierModule.h"
#include "Utils.h"
#include "BookDAO.h"


using namespace std;

CashierModule * CashierModule::cashierModule;
int CashierModule::numberItems = 0;
Book CashierModule::booksInCart[1024];
int CashierModule::quantities[1024];

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
			cout << Utils::toString(i + 1, quantities[i], booksInCart[i]) << endl;

		cout << "\t\t 1. Checkout" << endl;
		cout << "\t\t 2. Delete Items In Cart" << endl;
		cout << "\t\t 3. Back To Main Menu" << endl << endl;
		
		switch (Utils::showChoices(1,3)) {
		case 1: {
			double subtotal = 0.0;

			for (int i = 0; i < numberItems; i++)
				subtotal += booksInCart[i].getRetailPrice() * quantities[i];

			cout << "\t\t Subtotal:    " << fixed << setprecision(2) << subtotal << endl;
			cout << "\t\t Tax:          8%" << endl;
			cout << "\t\t Total:       " << fixed << setprecision(2) << subtotal * 1.08 << endl;
			cout << "Thank You For Shopping!" << endl << endl;
			exit(-1);
		}
			break;
		case 2:
			int number = 0;

			cout << "Enter Item Number: ";
			cin >> number;
			BookDAO::getInstance()->update(
				booksInCart[number - 1].getIsbn(),
				booksInCart[number - 1].getTitle(),
				booksInCart[number - 1].getAuthor(),
				booksInCart[number - 1].getPublisher(),
				booksInCart[number - 1].getQuantityOnHand(),
				booksInCart[number - 1].getWholesaleCost(),
				booksInCart[number - 1].getRetailPrice());
			for (int i = number - 1; i < numberItems - 1; i++)
				booksInCart[i] = booksInCart[i + 1];

			numberItems--;
			cout << "Your Book Has Been Removed From Receipt" << endl;
			system("pause");

			display();
			break;
		}
	}
	Module::showMainMenu();	
	
}
