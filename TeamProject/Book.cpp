#include "stdafx.h"
#include <iostream>
#include <string>
#include "Book.h"
#include "Utils.h"
//gfghgfdssdasdfdees
Book::Book(string isbn, string title, string author, string publisher,
	time_t dateAdded, int quantity, double wholesaleCost, double retailPrice) {
	setIsbn(isbn);
	setTitle(title);
	setAuthor(author);
	setPublisher(publisher);
	setDateAdded(dateAdded);
	setQuantityOnHand(quantity);
	setWholesaleCost(wholesaleCost);
	setRetailPrice(retailPrice);
}

void Book::setIsbn(string i) {
	isbn = i;
}

void Book::setTitle(string t) {
	if (t == "")
	{
		throw EmptyTitle();
	}
	else
	{
		title = t;
	}
}

void Book::setAuthor(string a) {
	if (a == "")
	{
		throw EmptyAuthor();
	}
	else
	{
		author = a;
	}
}

void Book::setPublisher(string p) {
	if (p == "")
	{
		throw EmptyPublisher();
	}
	else
	{
		publisher = p;
	}
}

void Book::setDateAdded(time_t d) {
	dateAdded = d;
}

void Book::setQuantityOnHand(int q) {
	if (q <= 0)
	{
		throw NonPositiveQuantity(q);
	}
	else
	{
		quantityOnHand = q;
	}

}

void Book::setWholesaleCost(double w) {
	if (w <= 0)
	{
		throw NonPositiveWholesalecost(w);
	}
	else
	{
		wholesaleCost = w;
	}
}

void Book::setRetailPrice(double r) {
	if (r <= 0)
	{
		throw NonPositiveRetailprice(r);
	}
	else
	{
		retailPrice = r;
	}
}

string Book::getIsbn() { return isbn; }
string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
string Book::getPublisher() { return publisher; }
time_t Book::getDateAdded() { return dateAdded; }
int Book::getQuantityOnHand() { return quantityOnHand; }
double Book::getWholesaleCost() { return wholesaleCost; }
double Book::getRetailPrice() { return retailPrice; }

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

