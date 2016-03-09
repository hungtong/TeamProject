#include "stdafx.h"
#include <iostream>
#include <string>
#include "Book.h"
#include "Utils.h"

Book::Book(string isbn, string title, string author, string publisher, 
			time_t dateAdded, int quantity, double wholesaleCost, double retailPrice) {
	this->isbn = isbn;
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->dateAdded = dateAdded;
	this->quantityOnHand = quantity;
	this->wholesaleCost = wholesaleCost;
	this->retailPrice = retailPrice;
}

Book::Book() {
	isbn = "";
	title = "";
	author = "";
	publisher = "";
	dateAdded = NULL;
	quantityOnHand = 0;
	wholesaleCost = 0;
	retailPrice = 0;
}

void Book::show() {
	string dateStr = Utils::toString(dateAdded);
	cout << "Book: isbn=" << isbn
		 << ", title=" << title 
		 << ", author=" << author 
		 << ", publisher=" << publisher 
		 << ", dateAdded=" << dateStr
		 << ", quantityOnHand=" << quantityOnHand 
		 << ", wholesaleCost=" << wholesaleCost 
		 << ", retailPrice=" << retailPrice << endl;
}

