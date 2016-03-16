/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class ReportModule Declaration

#pragma once
#include "stdafx.h"
#include<time.h>
#include <string>

#include "Module.h"
#include "Book.h"

using namespace std;

#ifndef REPORT_MODULE_H
#define REPORT_MODULE_H

class ReportModule : public Module {

private:
	static ReportModule * reportModule;
	ReportModule();

public:
	static int listingMode;
	static ReportModule * getInstance();

	void display();

	void displayInventoryListing();
	void displayInventoryWholesaleValue();
	void displayInventoryRetailValue();
	void displayListingByQuantity();
	void displayListingByCost();
	void displayListingByAge();
	void displayListingConfiguration();

	template<class Type> void printOut(Type value, int width);
	template<> void printOut(string value, int width);

};

#endif // REPORT_MODULE_H
