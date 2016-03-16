/*
	CIS22B_TeamProject_BookStore
	Archana Zone
	Hung Tong
	Michelle Liu
	Theodore Fausak
	Vasuki Sunder
*/

// Class CashierModule Declaration
#pragma once
#include "stdafx.h"
#include<time.h>
#include <string>

#include "Module.h"
#include "Book.h"

using namespace std;

#ifndef CASHIER_MODULE_H
#define CASHIER_MODULE_H

class CashierModule : public Module {

private:

	char datePurchase[11];
	static CashierModule * cashierModule;
	CashierModule();

public:
	static int numberItems;
	static Book booksInCart[1024];
	static int quantities[1024];

	char * getDatePurchase();
	static CashierModule * getInstance();

	void display();
};

#endif // CASHIER_MODULE_H
