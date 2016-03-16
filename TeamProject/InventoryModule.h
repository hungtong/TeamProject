/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class InventorModule Declaration
#pragma once
#include "stdafx.h"
#include <string>

#include "Module.h"
#include "Book.h"

using namespace std;

#ifndef INVENTORY_MODULE_H
#define INVENTORY_MODULE_H

class InventoryModule : public Module {

private:
	char datePurchase[11];
	static InventoryModule * inventoryModule;

	InventoryModule();

public:

	static const int SHOW_ISBN;
	static const int SHOW_TITLE;
	static const int SHOW_AUTHOR;
	static const int SHOW_PUBLISHER;
	static const int SHOW_DATE;
	static const int SHOW_QUANTITY;
	static const int SHOW_WHOLESALE;
	static const int SHOW_RETAIL_PRICE;

	static InventoryModule * getInstance();

	string askForISBN();

	int getBookPositionInCart(Book book);

	void display();
	void displayLookUpMenu();
	void displayAdd();
	void displayOptionsAfterLookUp(int thingToShow, Book bookObtained);
	void displayEdit();
	bool displayEditOptions(string isbn);
	void displayDelete();

	void showBooksByISBN();
	void showBooksByTitle();
	void showBooksByAuthor();
	void showBooksByPublisher();
	void showBooksByDate();
	void showBooksByQuantity();
	void showBooksByWholesale();
	void showBooksByRetailPrice();
};

#endif // INVENTORY_MODULE_H

