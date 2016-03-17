/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class CashierModule Specification

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>

#include "Module.h"
#include "ReportModule.h"
#include "Book.h"
#include "BookDAO.h"
#include "Utils.h"

//get and set varibles
ReportModule * ReportModule::reportModule;
int ReportModule::listingMode = 1;

ReportModule::ReportModule() {
	setName("Report Module");
	setDescription("analyze information in inventory database module");
}

ReportModule * ReportModule::getInstance() {//check if NULL
	if (reportModule == NULL) {
		reportModule = new ReportModule();
	}
	return reportModule;
}

template<class Type> void ReportModule::printOut(Type value, int width) {
	cout << left << setw(width) << value;
}

template<> void ReportModule::printOut(string value, int width) {
	cout << left << setw(width) << value;
}
/*
Shows the various methods of vieweing the inventory
Verifies whether user input is valid
Displays the right inventory depending on user choice
*/

void ReportModule::display() {//display report module
	system("CLS");
	cout << "\t\t  Serendipity Booksellers" << endl;
	cout << "\t\t\t Reports" << endl << endl;
	cout << "\t\t 1. Inventory Listing" << endl;//give user options 1-8
	cout << "\t\t 2. Inventory Wholesale Value" << endl;
	cout << "\t\t 3. Inventory Retail Value" << endl;
	cout << "\t\t 4. Inventory by Quantity" << endl;
	cout << "\t\t 5. Inventory by Cost" << endl;
	cout << "\t\t 6. Inventory by Age" << endl;
	cout << "\t\t 7. Listing Configuration" << endl;
	cout << "\t\t 8. Return to Main Menu" << endl << endl;

	int choice = 0;//preset to 0
	do {
		cout << "\t\t Enter Your Choice: ";
		cin >> choice;
		if (choice < 1 || choice > 8)//require user to enter 1-8
			cout << "\t\t Invalid Command. Please Enter Your Choice Again!!!" << endl << endl;
	} while (choice < 1 || choice > 8);

	switch (choice) {
	case 1:
		displayInventoryListing();//if 1: display the inventory
		display();
		break;
	case 2:
		displayInventoryWholesaleValue();//if 2: desplay the inventory and wholesale cost
		display();
		break;
	case 3:
		displayInventoryRetailValue();//if 3: : display the inventory and retail price
		display();
		break;
	case 4:
		displayListingByQuantity();//if 4: : display the inventory by quantity
		display();
		break;
	case 5:
		displayListingByCost();//if 5: : display the inventory by cost
		display();
		break;
	case 6:
		displayListingByAge();//if 6: : display the inventory by age
		display();
		break;
	case 7:
		displayListingConfiguration();// if 7: : display the inventory configuration
		display();
		break;
	case 8:
		Module::showMainMenu();// if 8: bring user back to main menu
		break;
	}
}
/*
Displays the Inventory of books with the ISBN, title, author, and publisher
*/

void ReportModule::displayInventoryListing() {
	system("CLS");
	Book * books = BookDAO::getInstance()->getBooks();
	cout << "   ";
	printOut("ISBN", 20);
	printOut("Title", 22);
	printOut("Author", 19);
	printOut("Publisher", 15);
	cout << "\n------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < BookDAO::getInstance()->getNumBooks(); i++) {
		printOut(books[i].getIsbn(), 20);
		printOut(books[i].getTitle(), 25);
		printOut(books[i].getAuthor(), 19);
		printOut(books[i].getPublisher(), 15);
		cout << endl;
	}
	system("pause");
}
/*
Sorts the books by Wholesale cost and then displays them in that order
*/

void ReportModule::displayInventoryWholesaleValue() {
	system("CLS");
	Book * books = BookDAO::getInstance()->getBooks();

	Utils::sortByWholesaleCost(0, BookDAO::numBooks - 1, books, ReportModule::listingMode);

	cout << "   ";
	printOut("ISBN", 20);
	printOut("Title", 22);
	printOut("Wholesale Cost", 20);
	cout << "\n------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < BookDAO::getInstance()->getNumBooks(); i++) {
		printOut(books[i].getIsbn(), 20);
		printOut(books[i].getTitle(), 27);
		printOut(books[i].getWholesaleCost(), 20);
		cout << endl;
	}
	system("pause");
}
/*
Sorts the books by retail value and then displays them in that order
*/
void ReportModule::displayInventoryRetailValue() {
	system("CLS");
	Book * books = BookDAO::getInstance()->getBooks();

	Utils::sortByRetailPrice(0, BookDAO::numBooks - 1, books, ReportModule::listingMode);

	cout << "   ";
	printOut("ISBN", 20);
	printOut("Title", 22);
	printOut("Retail Price", 20);
	cout << "\n------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < BookDAO::getInstance()->getNumBooks(); i++) {
		printOut(books[i].getIsbn(), 20);
		printOut(books[i].getTitle(), 27);
		printOut(books[i].getRetailPrice(), 20);
		cout << endl;
	}
	system("pause");

}
/*
Displays books in order of the quantity
*/

void ReportModule::displayListingByQuantity() {
	system("CLS");
	Book * books = BookDAO::getInstance()->getBooks();

	Utils::sortByQuantity(0, BookDAO::numBooks - 1, books, ReportModule::listingMode);

	cout << "   ";
	printOut("ISBN", 20);
	printOut("Title", 22);
	printOut("Quantity", 20);
	cout << "\n------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < BookDAO::getInstance()->getNumBooks(); i++) {
		printOut(books[i].getIsbn(), 20);
		printOut(books[i].getTitle(), 27);
		printOut(books[i].getQuantityOnHand(), 20);
		cout << endl;
	}
	system("pause");

}

void ReportModule::displayListingByCost() {

}
/*
Displays books in the order of their date added
*/

void ReportModule::displayListingByAge() {
	system("CLS");
	Book * books = BookDAO::getInstance()->getBooks();

	Utils::sortByAge(0, BookDAO::numBooks - 1, books, ReportModule::listingMode);

	cout << "   ";
	printOut("ISBN", 20);
	printOut("Title", 27);
	printOut("Date Added", 20);
	cout << "\n------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < BookDAO::getInstance()->getNumBooks(); i++) {
		printOut(books[i].getIsbn(), 20);
		printOut(books[i].getTitle(), 27);
		printOut(Utils::toString(books[i].getDateAdded()), 20);
		cout << endl;
	}
	system("pause");

}

void ReportModule::displayListingConfiguration() {
	system("CLS");
	cout << "\t\t  Serendipity Booksellers" << endl;
	cout << "\t\t\t Reports" << endl;
	cout << "\t\t Listing Configuration" << endl << endl;
	cout << "\t1. Listing In Database Order (By Default)"<< endl;
	cout << "\t2. Listing In Increasing Order" << endl;
	cout << "\t3. Listing In Decreasing Order" << endl;

	int choice = 0;
	do {
		cout << "\t\t Enter Your Choice: ";
		cin >> choice;
		if (choice < 1 || choice > 3)
			cout << "\t\t Invalid Command. Please Enter Your Choice Again!!!" << endl << endl;
	} while (choice < 1 || choice > 3);

	switch (choice) {
	case 1:
		listingMode = 1;
		break;
	case 2:
		listingMode = 2;
		break;
	case 3:
		listingMode = 3;
		break;
	}
	system("pause");

}
