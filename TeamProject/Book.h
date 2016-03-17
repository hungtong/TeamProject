/*
	CIS22B_TeamProject_BookStore
	Archana Sharma
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

//Class Book Declaration

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <time.h>
#include "Book.h"

using namespace std;

/*
ISBN: This is the International Standard Book Number. It is a unique number assigned to each book by the publisher.
Title: The title of the book.
Author: The book’s author.
Publisher: The company that publishes the book.
Date Added: The date the book was added to the inventory.
Quantity-On-Hand: The number of copies of the book in inventory.
Wholesale Cost: The price paid by Serendipity for each copy of the book.
Retail Price: The price Serendipity is charging for each copy of the book.
*/
#ifndef BOOK_H
#define BOOK_H
class Book {
private:
	string isbn;
	string title;
	string author;
	string publisher;
	time_t dateAdded;
	int quantityOnHand;
	double wholesaleCost;
	double retailPrice;
public:
	//Exception class for empty title
	class EmptyTitle {};

	//Exception class for empty author
	class EmptyAuthor {};

	//Exception class for empty publisher
	class EmptyPublisher {};

	//Exception class for non positive quantity
	class NonPositiveQuantity {
	private:
		int quantity;
	public:
		NonPositiveQuantity(int q) {
			quantity = q;
		}
		int getValue() {
			return quantity;
		}
	};

	//Exception class for non positive wholesalecost
	class NonPositiveWholesalecost
	{
	private:
		int wholesalecost;
	public:
		NonPositiveWholesalecost(int w) {
			wholesalecost = w;
		}
		int getValue() {
			return wholesalecost;
		}
	};

	//Exception class for non positive retailprice
	class NonPositiveRetailprice
	{
	private:
		int retailprice;
	public:
		NonPositiveRetailprice(int r) {
			retailprice = r;
		}
		int getValue() {
			return retailprice;
		}
	};

	Book();
	Book(string isbn, string title, string author, string publisher, time_t dateAdded,
		int quantity, double wholesaleCost, double retailPrice);

	void setIsbn(string i);//54894784
	void setTitle(string t);
	void setAuthor(string a);
	void setPublisher(string p);
	void setDateAdded(time_t d);
	void setQuantityOnHand(int q);
	void setWholesaleCost(double w);
	void setRetailPrice(double r);
	string getIsbn();
	string getTitle();
	string getAuthor();
	string getPublisher();
	time_t getDateAdded();
	int getQuantityOnHand();
	double getWholesaleCost();
	double getRetailPrice();
};

#endif
