#include "UserEvents.h"
#include <iostream>
#include "Main.h"

using std::endl;
using std::cout;
using std::cin;

int main()
{


	UserEvents UsrEvt;

	CallUserFunctionADD(UsrEvt);

	system("pause");

	return 0;
}

void CallUserFunctionADD(UserEvents &UsrEvt)
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

	UsrEvt.Choose("Add", A, &Result);

	cout << "A+B = " << Result << endl;
}
