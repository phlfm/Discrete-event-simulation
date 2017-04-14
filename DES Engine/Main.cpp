// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"
#include <iostream>
#include "Main.h"

using std::endl;
using std::cout;
using std::cin;

int main()
{


	UserEvents UsrEvt = UserEvents();

	//TEST_UserFunctionADD(UsrEvt);


	system("pause");

	return 0;
}

void TEST_UserFunctionADD(UserEvents &UsrEvt)
{
	int A[2];
	int Result;
	std::string EventAlias = "Add";

	cout << "Test User Event Choose Function with Add User Function Implemented" << endl;
	cout << "Enter an Integer A: ";
	cin >> A[0];
	cout << endl << "Enter another integer B: ";
	std::cin >> A[1];
	cout << endl;

	UsrEvt.Choose(EventAlias, A, &Result);

	cout << "A+B = " << Result << endl;
}
