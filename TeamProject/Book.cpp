/*
	CIS22B_TeamProject_BookStore
	Archana Sharma
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class Book Specification
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Book.h"
#include "Utils.h"

/*
	Explicit Constructor to construct an object Book
	Initialize all object's fields
*/
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

/*
	Implicit Constructor to construct an object Book
	Initialize all object's fields
*/
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

/*
 	Specify ISBN
 	@param r : desired Retail Price
 */
void Book::setIsbn(string i) {
	isbn = i;
}

/*
	Specify Title
	@param t : desired Title
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

/*
	Specify Author
	@param a : desired Author
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

/*
	Specify Publisher
	@param p : desired Publisher
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

/*
	Specify Date Added
	@param d : desired Time
 */
void Book::setDateAdded(time_t d) {
	dateAdded = d;
}

/*
	Specify Quantity On Hand
	@param q : desired Quantity On Hand
 */
void Book::setQuantityOnHand(int q) {
	if (q < 0)
	{
		throw NonPositiveQuantity(q);
	}
	else
	{
		quantityOnHand = q;
	}

}

/*
	Specify Wholesal Cost
	@param w : desired Wholesale Cost
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

/*	
	Specify Retail Price
	@param r : desired Retail Price
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

/*	
	Return ISBN
	@return ISBN
 */
string Book::getIsbn() { return isbn; }

/*	
	Return Title
	@return Title
 */
string Book::getTitle() { return title; }

/*	
	Return Author
	@return Author
 */
string Book::getAuthor() { return author; }

/*	
	Return Publisher
	@return Publisher
 */
string Book::getPublisher() { return publisher; }

/*	
	Return Date Added
	@return Date Added
 */
time_t Book::getDateAdded() { return dateAdded; }

/*	
	Return Quantity-On-Hand
	@return Quantity-On-Hand
 */
int Book::getQuantityOnHand() { return quantityOnHand; }

/*	
	Return Wholesale Cost
	@return Wholesale Cost
 */
double Book::getWholesaleCost() { return wholesaleCost; }

/*	
	Return Retail Price
	@return Retail Price
 */
double Book::getRetailPrice() { return retailPrice; }

