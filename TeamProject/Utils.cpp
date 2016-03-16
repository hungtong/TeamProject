#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>

#include "Book.h"
#include "Utils.h"

	using namespace std;

const int Utils::DEFAULT = 1;
const int Utils::INCREASING = 2;
const int Utils::DECREASING = 3;

int Utils::showChoices(int lowerBound, int upperBound) {
	int choice = 0;
	do {
		cout << "\t\t Enter Your Choice: ";
		cin >> choice;
		if (choice < lowerBound || choice > upperBound)
			cout << "\t\t Invalid Option. Please Enter Your Choice Again!!!" << endl << endl;
	} while (choice < lowerBound || choice > upperBound);
	return choice;
}

string Utils::toString(int itemNumber, int quantity, Book book) {
	string bookString = "";
	bookString += to_string(itemNumber) + "\n";
	bookString += "\t ISBN:              " + book.getIsbn() + "\n";
	bookString += "\t Title:             " + book.getTitle() + "\n";
	bookString += "\t Author:            " + book.getAuthor() + "\n";
	bookString += "\t Publisher:         " + book.getPublisher() + "\n";
	bookString += "\t Date Added:        " + toString(book.getDateAdded()) + "\n";
	bookString += "\t Quantity:          " + to_string(quantity) + "\n";

	ostringstream stream;
	stream << fixed << setprecision(2) << book.getRetailPrice();
	bookString += "\t Retail Price:      " + stream.str() + "\n";

	return bookString;
}

// Converts time_t into string of format YY-MM-DD HH:MM:SS
string Utils::toString(time_t const &time) {
	tm * timeinfo = localtime(&time);
	int year = timeinfo->tm_year + 1900;
	int month = timeinfo->tm_mon + 1;
	int day = timeinfo->tm_mday;
	int hour = timeinfo->tm_hour;
	int min = timeinfo->tm_min;
	int sec = timeinfo->tm_sec;

	string dateStr = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
	string timeStr = to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);

	return dateStr + " " + timeStr;
}

// Parse string of format YY-MM-DD HH:MM:SS into time_t
time_t Utils::fromString(string str) {
	// separate date and time
	istringstream dateTimeStream(str);
	string date;
	getline(dateTimeStream, date, ' ');
	string time;
	getline(dateTimeStream, time, ' ');

	// parse date
	istringstream dateStream(date);
	string yearStr;
	getline(dateStream, yearStr, '-');
	int year = stoi(yearStr);
	string monthStr;
	getline(dateStream, monthStr, '-');
	int month = stoi(monthStr);
	string dayStr;
	getline(dateStream, dayStr, '-');
	int day = stoi(dayStr);

	// parse time
	istringstream timeStream(time);
	string hourStr;
	getline(timeStream, hourStr, ':');
	int hour = stoi(hourStr);
	string minStr;
	getline(timeStream, minStr, ':');
	int min = stoi(minStr);
	string secStr;
	getline(timeStream, secStr, ':');
	int sec = stoi(secStr);

	struct tm timeinfo = { 0 };

	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = day;
	timeinfo.tm_hour = hour;
	timeinfo.tm_min = min;
	timeinfo.tm_sec = sec;

	return mktime(&timeinfo);
}

// Converts book object into csv (comma separated value) entry
string Utils::toCsv(Book *b) {
	time_t dateAdded = b->getDateAdded();
	string dateStr = Utils::toString(dateAdded);
	string csv = b->getIsbn() + "," + b->getTitle() + "," + b->getAuthor() + ","
		+ b->getPublisher() + "," + dateStr + "," + to_string(b->getQuantityOnHand()) + ",";

	ostringstream stream1, stream2;
	stream1 << fixed << setprecision(2) << b->getWholesaleCost();
	csv += stream1.str() + ",";

	stream2 << fixed << setprecision(2) << b->getRetailPrice();
	csv += stream2.str();

	return csv;
}

// Parse isbn from csv
string Utils::parseIsbn(string line) {
	istringstream tokens(line);
	string isbn = "";
	getline(tokens, isbn, ',');
	return isbn;
}

// Parse csv (comma separated value) entry into Book object
Book Utils::fromCsv(string line) {
	istringstream tokens(line);

	string isbn = "";
	getline(tokens, isbn, ',');

	string title = "";
	getline(tokens, title, ',');

	string author = "";
	getline(tokens, author, ',');

	string publisher = "";
	getline(tokens, publisher, ',');

	string dateStr = "";
	getline(tokens, dateStr, ',');
	time_t dateAdded = fromString(dateStr);

	string quantityOnHandStr = "";
	getline(tokens, quantityOnHandStr, ',');
	int quantityOnHand = stoi(quantityOnHandStr);

	string wholesaleCostStr = "";
	getline(tokens, wholesaleCostStr, ',');
	double wholesaleCost = stod(wholesaleCostStr);

	string retailPriceStr = "";
	getline(tokens, retailPriceStr, ',');
	double retailPrice = stod(retailPriceStr);
	try
	{
		Book b(isbn, title, author, publisher, dateAdded, quantityOnHand, wholesaleCost, retailPrice);
		return  b;
	}
	catch (Book::EmptyTitle)
	{
		cout << "Error parsing file:Empty string given for title." << isbn << endl;
		exit(-1);
	}
	catch (Book::EmptyAuthor)
	{
		cout << "Error parsing file:Empty string given for author." << isbn << endl;
		exit(-1);
	}
	catch (Book::EmptyPublisher)
	{
		cout << "Error parsing file:Empty string given for publisher." << isbn << endl;
		exit(-1);
	}
	catch (Book::NonPositiveQuantity q)
	{
		cout << "Error parsing file:Non positive value given for quantity. isbn=" << isbn << ", quantity=" << q.getValue() << endl;
		exit(-1);
	}
	catch (Book::NonPositiveWholesalecost w)
	{
		cout << "Error parsing file:Non positive value given for wholesalecost. isbn" << isbn << ", wholesaleprice=" << w.getValue() << endl;
		exit(-1);
	}
	catch (Book::NonPositiveRetailprice r)
	{
		cout << "Error parsing file:Non positive value given for retailprice.isbn" << isbn << ", retailprice=" << r.getValue() << endl;
		exit(-1);
	}
	catch (string message)
	{
		cout << "Error parsing file: " << message << isbn << endl;
		exit(-1);
	}
}

string Utils::toLowerCase(string givenString) {
	for (int i = 0; i < givenString.length(); i++)
		if (givenString[i] >= 'A' && givenString[i] <= 'Z')
			givenString[i] = givenString[i] + 32;
	return givenString;
}

void Utils::displayBookInformation(Book book) {
	cout << "\tISBN            \t" << book.getIsbn() << endl;
	cout << "\tTitle           \t" << book.getTitle() << endl;
	cout << "\tAuthor          \t" << book.getAuthor() << endl;
	cout << "\tPublisher       \t" << book.getPublisher() << endl;
	cout << "\tDate Added      \t" << toString(book.getDateAdded()) << endl;
	cout << "\tQuantity-On-Hand\t" << book.getQuantityOnHand() << endl;
	cout << "\tWholesale Cost  \t" << setprecision(2) << book.getWholesaleCost() << endl;
	cout << "\tRetail Price    \t" << setprecision(2) << book.getRetailPrice() << endl << endl;
}

void Utils::swap(Book  * a, Book * b) {
	Book c = *a;
	*a = *b;
	*b = c;
}

void Utils::sortByAge(int left, int right, Book book[], int sortMode) {
	if (sortMode != DEFAULT && left <= right) {
		int x = left;
		int y = right;
		int median = x + (y - x) / 2;
		do {

			if (sortMode == INCREASING) {
				while (difftime(book[x].getDateAdded(), book[median].getDateAdded()) < 0)
					x++;
				while (difftime(book[y].getDateAdded(), book[median].getDateAdded()) > 0)
					y--;
			}

			if (sortMode == DECREASING) {
				while (difftime(book[x].getDateAdded(), book[median].getDateAdded()) > 0)
					x++;
				while (difftime(book[y].getDateAdded(), book[median].getDateAdded()) < 0)
					y--;
			}

			if (x <= y) {
				if (x < y) swap(&book[x], &book[y]);
				x++; y--;
			}
		} while (x <= y);
		sortByAge(left, y, book, sortMode);
		sortByAge(x, right, book, sortMode);
	}
}

void Utils::sortByQuantity(int left, int right, Book book[], int sortMode) {
	if (sortMode != DEFAULT && left <= right) {
		int x = left;
		int y = right;
		int median = x + (y - x) / 2;
		do {

			if (sortMode == INCREASING) {
				while (book[x].getQuantityOnHand() < book[median].getQuantityOnHand())
					x++;
				while (book[y].getQuantityOnHand() > book[median].getQuantityOnHand())
					y--;
			}

			if (sortMode == DECREASING) {
				while (book[x].getQuantityOnHand() > book[median].getQuantityOnHand())
					x++;
				while (book[y].getQuantityOnHand() < book[median].getQuantityOnHand())
					y--;
			}

			if (x <= y) {
				if (x < y) swap(&book[x], &book[y]);
				x++; y--;
			}
		} while (x <= y);
		sortByQuantity(left, y, book, sortMode);
		sortByQuantity(x, right, book, sortMode);
	}
}

void Utils::sortByWholesaleCost(int left, int right, Book book[], int sortMode) {
	if (sortMode != DEFAULT && left <= right) {
		int x = left;
		int y = right;
		int median = x + (y - x) / 2;
		do {

			if (sortMode == INCREASING) {
				while (book[x].getWholesaleCost() < book[median].getWholesaleCost())
					x++;
				while (book[y].getWholesaleCost() > book[median].getWholesaleCost())
					y--;
			}

			if (sortMode == DECREASING) {
				while (book[x].getWholesaleCost() > book[median].getWholesaleCost())
					x++;
				while (book[y].getWholesaleCost() < book[median].getWholesaleCost())
					y--;
			}

			if (x <= y) {
				if (x < y) swap(&book[x], &book[y]);
				x++; y--;
			}
		} while (x <= y);
		sortByWholesaleCost(left, y, book, sortMode);
		sortByWholesaleCost(x, right, book, sortMode);
	}
}

void Utils::sortByRetailPrice(int left, int right, Book book[], int sortMode) {
	if (sortMode != DEFAULT && left <= right) {
		int x = left;
		int y = right;
		int median = x + (y - x) / 2;
		do {

			if (sortMode == INCREASING) {
				while (book[x].getRetailPrice() < book[median].getRetailPrice())
					x++;
				while (book[y].getRetailPrice() > book[median].getRetailPrice())
					y--;
			}

			if (sortMode == DECREASING) {
				while (book[x].getRetailPrice() > book[median].getRetailPrice())
					x++;
				while (book[y].getRetailPrice() < book[median].getRetailPrice())
					y--;
			}

			if (x <= y) {
				if (x < y) swap(&book[x], &book[y]);
				x++; y--;
			}
		} while (x <= y);
		sortByRetailPrice(left, y, book, sortMode);
		sortByRetailPrice(x, right, book, sortMode);
	}
}

// read integer value from user input
int Utils::readInt(char * message) {
	int x;
	cout << message;
	while (!(cin >> x))
	{
		cout << "Please provide an interger value." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << message;
	}
	return x;
}

//read double from user input
double Utils::readDouble(char * message) {
	double x;
	cout << message;
	while (!(cin >> x))
	{
		cout << "Please provide an float value." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		cout << message;
	}
	return x;
}

