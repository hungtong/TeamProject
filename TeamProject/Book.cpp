#include "stdafx.h"
#include <iostream>
#include <string>
#include "Book.h"
#include "Utils.h"

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

/**
 * set the book's isbn
 * 
 * @param i isbn number entered by user
 */
void Book::setIsbn(string i) {
	isbn = i;
}

/**
 * set the book's title
 * 
 * @param t book title entered by user
 */
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

/**
 * set the book's author
 * 
 * @param a  book author entered by user
 */
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

/**
 * set the book's publisher
 * 
 * @param p  book publisher entered by user
 */
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

/**
 * set the date the book was added  
 * 
 * @param d  date the book was added entered by user
 */
void Book::setDateAdded(time_t d) {
	dateAdded = d;
}

/**
 * set quantities on hand for a book
 * 
 * @param q  quantity entered by user
 */
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

/**
 * set the wholesale price for the book 
 * 
 * @param w  wholesale price entered by user
 */
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

/**
 * set the retail price for the book 
 * 
 * @param r  retail price entered by user
 */
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

/**
 * return the isbn number of the book 
 * 
 * @return the isbn number of the book 
 */
string Book::getIsbn() { return isbn; }
/**
 * return the title of the book 
 * 
 * @return title of the book 
 */
string Book::getTitle() { return title; }
/**
 * return author of the book 
 * 
 * @return author of the book 
 */
string Book::getAuthor() { return author; }
/**
 * return publisher of the book 
 * 
 * @return publisher of the book 
 */
string Book::getPublisher() { return publisher; }
/**
 * return date the book was added  
 * 
 * @return date the book was added  
 */
time_t Book::getDateAdded() { return dateAdded; }
/**
 * return quantity on hand for the book 
 * 
 * @return quantity on hand
 */
int Book::getQuantityOnHand() { return quantityOnHand; }
/**
 * return wholesale cost of the book
 * 
 * @return wholesale cost of the book
 */
double Book::getWholesaleCost() { return wholesaleCost; }
/**
 * return retail price of the book
 * 
 * @return retail price
 */
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

