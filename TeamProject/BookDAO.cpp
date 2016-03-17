/*
	CIS22B_TeamProject_BookStore
	Archana Sharma
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class BookDAO Specification 

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<sstream>
#include<string>

#include "Book.h"
#include "BookDAO.h"
#include "Utils.h"
#include "ReportModule.h"

using namespace std;

BookDAO * BookDAO::bookDAO;
int BookDAO::numBooks = 0;
int BookDAO::numPossibleBooks = 0;
const string BookDAO::BOOK_FILE_NAME = "Books.txt";

/*
	Implicit Constructor to read input file and populate books array

	for each line in file:
		parse line (csv entry) and create a book object b
		if b.quantityOnHand > 0:
			add b to books array
*/
BookDAO::BookDAO() {
	ifstream inputFile(BOOK_FILE_NAME);
	string line = "";
	while (getline(inputFile, line)) {
		Book b = Utils::fromCsv(line);
		if (b.getQuantityOnHand() > 0) {
			books[numBooks] = b;
			numBooks++;
		}
	}
	inputFile.close();
}

/*
	Function Description:
		- Singleton to make sure BookDAO is only constructed one time
	
	Implementation:
		- If (bookDAO is not constructed yes) construct one and return bookDAO
		
	@return pointer of BookDAO
*/
BookDAO * BookDAO::getInstance() {
	if (bookDAO == NULL) {
		bookDAO = new BookDAO();
	}
	return bookDAO;
}

/*
	Persist a book object into file

	Open the books data file stream in append mode
	Convert the given book object into csv string representation
	Write the csv string into file
	Close the file stream	
*/
void BookDAO::appendIntoFile(Book *b) {
	fstream file;
	file.open(BOOK_FILE_NAME, ios::app);
	string csvRecord = Utils::toCsv(b);
	file << csvRecord << endl;
	file.close();
}

/*
	Store all book objects in memory into data file.
	This operation rewrites the data file.

	Open the books data file stream
	for each book b in books array:
		Convert book object b into csv string representation
		Write the csv string into file
	Close the file stream
*/
void BookDAO::storeToFile() {
	ofstream outputFile(BOOK_FILE_NAME);
	for (int i = 0; i < numBooks; i++) {
		string csvRecord = Utils::toCsv(&books[i]);
		outputFile << csvRecord << endl;
	}
	outputFile.close();
}

/*
Checks if a book exists by the given isbn.
*/
bool BookDAO::existsByIsbn(string isbn) {
	for (int i = 0; i < numBooks; i++) {
		if (books[i].getIsbn().find(isbn) != std::string::npos)
			return true;
	}
	return false;
}

/*
Inserts a book.

First validates that no book exists by the provided isbn number.
Validates the input and creates a book object.
The new object is then persisted in memory and into the data file.
*/
void BookDAO::insert(string isbn, string title, string author, string publisher,
	int quantityOnHand, double wholesaleCost, double retailPrice) {
	//  Validate that no book exists by this isbn number.
	if (existsByIsbn(isbn)) {
		cout << "\t\t Book already exist!" << endl;
		return;
	}

	time_t  dateAdded = time(NULL);
	try
	{
		Book b(isbn, title, author, publisher, dateAdded, quantityOnHand, wholesaleCost, retailPrice);
		books[numBooks] = b;
		numBooks++;
		appendIntoFile(&b);
		cout << "\t\t Your Book Has Been Inserted Successfully!" << endl;
	}
	catch (Book::EmptyTitle)
	{
		cout << "Error:Empty string given for title.\n";
	}
	catch (Book::EmptyAuthor)
	{
		cout << "Error:Empty string given for author.\n";
	}
	catch (Book::EmptyPublisher)
	{
		cout << "Error:Empty string given for publisher.\n";
	}
	catch (Book::NonPositiveQuantity)
	{
		cout << "Error:non positive value given for quantity.\n";
	}
	catch (Book::NonPositiveWholesalecost)
	{
		cout << "Error:non positive value given for wholesalecost.\n";
	}
	catch (Book::NonPositiveRetailprice)
	{
		cout << "Error:non positive value given for retailprice.\n";
	}
	catch (string message)
	{
		cout << "Error: " << message << endl;
	}
}

/*
Updates attributes in a book.

First checks if the object exists by the given isbn number.
Validates the input and update the book information.
The modified object is then persisted into the data file.
*/
void BookDAO::update(string isbn, string title, string author, string publisher,
	int quantityOnHand, double wholesaleCost, double retailPrice)
{
	Book * b = nullptr;
	int i = 0;
	for (i = 0; i < numBooks; i++)
	{
		if (books[i].getIsbn() == isbn)
		{
			b = &books[i];
			break;
		}
	}
	if (b == nullptr)
	{
		cout << "Book doesn't exist" << endl;
		return;
	}
	try {
		b->setTitle(title);
		b->setAuthor(author);
		b->setPublisher(publisher);
		b->setQuantityOnHand(quantityOnHand);
		b->setRetailPrice(retailPrice);
		b->setWholesaleCost(wholesaleCost);
		storeToFile();
	}
	catch (Book::EmptyTitle)
	{
		cout << "Error:Empty string given for title.\n";
	}
	catch (Book::EmptyAuthor)
	{
		cout << "Error:Empty string given for author.\n";
	}
	catch (Book::EmptyPublisher)
	{
		cout << "Error:Empty string given for publisher.\n";
	}
	catch (Book::NonPositiveQuantity)
	{
		cout << "Error:non positive value given for quantity.\n";
	}
	catch (Book::NonPositiveWholesalecost)
	{
		cout << "Error:non positive value given for wholesalecost.\n";
	}
	catch (Book::NonPositiveRetailprice)
	{
		cout << "Error:non positive value given for retailprice.\n";
	}
	catch (string message)
	{
		cout << "Error: " << message << endl;
	}
}

/*
Delete a book by its isbn number
*/
void BookDAO::deleteByIsbn(string isbn)
{
	int i = 0;
	for (i = 0; i < numBooks; i++)
	{
		if (books[i].getIsbn() == isbn)
		{
			break;
		}
	}
	if (i == numBooks)
	{
		cout << "Book doesn't exits" << endl;
		return;
	}
	for (int j = i + 1; j < numBooks; j++)
	{
		books[j - 1] = books[j];
	}
	numBooks--;
	cout << "\nBook Has Been Deleted Successfully!" << endl;
	storeToFile();
}

/*
Get all the books persisted in memory.
*/
Book * BookDAO::getBooks() {
	Book * copied = new Book[1024];
	for (int i = 0; i < numBooks; i++) {
		copied[i] = books[i];
	}
	return copied;
}

/*
Get all books by the given isbn number.
*/
Book * BookDAO::getBooksByISBN(string keyword) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;
	string lowerCaseKeyWord = Utils::toLowerCase(keyword);
	string lowerCaseISBN = "";

	for (int i = 0; i < numBooks; i++) {
		lowerCaseISBN = Utils::toLowerCase(books[i].getIsbn());
		if (lowerCaseISBN.find(lowerCaseKeyWord) != std::string::npos ||
			lowerCaseKeyWord.find(lowerCaseISBN) != std::string::npos)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given title.
*/
Book * BookDAO::getBooksByTitle(string keyword) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;
	string lowerCaseKeyWord = Utils::toLowerCase(keyword);
	string lowerCaseTitle = "";

	for (int i = 0; i < numBooks; i++) {
		lowerCaseTitle = Utils::toLowerCase(books[i].getTitle());
		if (lowerCaseTitle.find(lowerCaseKeyWord) != std::string::npos ||
			lowerCaseKeyWord.find(lowerCaseTitle) != std::string::npos)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given author.
*/
Book * BookDAO::getBooksByAuthor(string keyword) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;
	string lowerCaseKeyWord = Utils::toLowerCase(keyword);
	string lowerCaseAuthor = "";

	for (int i = 0; i < numBooks; i++) {
		lowerCaseAuthor = Utils::toLowerCase(books[i].getAuthor());
		if (lowerCaseAuthor.find(lowerCaseKeyWord) != std::string::npos ||
			lowerCaseKeyWord.find(lowerCaseAuthor) != std::string::npos)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given publisher.
*/
Book * BookDAO::getBooksByPublisher(string keyword) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;
	string lowerCaseKeyWord = Utils::toLowerCase(keyword);
	string lowerCasePublisher = "";

	for (int i = 0; i < numBooks; i++) {
		lowerCasePublisher = Utils::toLowerCase(books[i].getPublisher());
		if (lowerCasePublisher.find(lowerCaseKeyWord) != std::string::npos ||
			lowerCaseKeyWord.find(lowerCasePublisher) != std::string::npos)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given date.
*/
Book * BookDAO::getBooksByAge(string age) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;
	time_t date = Utils::fromString(age);

	for (int i = 0; i < numBooks; i++) {
		if (difftime(date, books[i].getDateAdded()) == 0)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	Utils::sortByAge(0, numberPossibleBooks - 1, possibleBooks, ReportModule::listingMode);
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given quantity.
*/
Book * BookDAO::getBooksByQuantity(int quantity) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;

	for (int i = 0; i < numBooks; i++) {
		if (books[i].getQuantityOnHand() == quantity)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given wholesale cost.
*/
Book * BookDAO::getBooksByWholesaleCost(double wholesaleCost) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;

	for (int i = 0; i < numBooks; i++) {
		if (books[i].getWholesaleCost() == wholesaleCost)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

/*
Get all books by the given retail price.
*/
Book * BookDAO::getBooksByRetailPrice(double price) {
	Book * possibleBooks = new Book[1024];
	int numberPossibleBooks = 0;

	for (int i = 0; i < numBooks; i++) {
		if (books[i].getRetailPrice() == price)
			possibleBooks[numberPossibleBooks++] = books[i];
	}
	numPossibleBooks = numberPossibleBooks;
	return possibleBooks;
}

