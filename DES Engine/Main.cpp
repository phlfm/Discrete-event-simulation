// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include "Main.h"


using std::endl;
using std::cout;
using std::cin;

int main()
{


	UserEvents UsrEvt = UserEvents();
	GlobalVariables GlobVar = GlobalVariables();

	//TEST_UserFunctionADD(UsrEvt);
	TEST_GlobalVariableSetGetType(GlobVar);


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

void TEST_GlobalVariableSetGetType(GlobalVariables &GV)
{
#include <string>

	int A[2];
	std::string Name;

	//Get Input
	cout << "Enter an Integer A: ";
	cin >> A[0];
	cout << endl << "Enter another integer B: ";
	std::cin >> A[1];
	cout << endl;
	cout << endl << "Enter your name: ";
	std::getline (cin >> std::ws, Name); //cin >> std::ws removes whitespace so it doesnt catch a \n at the end and jumps the getline
	cout << endl;

	// Set Variables
	GV.VarSet((std::string)"Nombre", Name);
	GV.VarSet("iA", A[0]);
	GV.VarSet("iB", A[1]);
	GV.VarSet("fC", ((float)(A[0]) / A[1]));

	// Check Variable Types
	cout << endl << "iA type: "		<< GV.VarGet_Type("iA");
	cout << endl << "iB type: "		<< GV.VarGet_Type("iB");
	cout << endl << "fC type: "		<< GV.VarGet_Type("fC");
	cout << endl << "Nombre type: "	<< (GV.VarGet_Type("Nombre"));

	// Print out some variables
	cout << endl << GV.VarGet_String("Nombre") << ", A/B is: ";
	cout << "fC = " << GV.VarGet_Float("fC") << "\n\n";

	// Change variable types (int -> float) (int -> string)
	GV.VarSet("iA", GV.VarGet_Float("fC")*3.1415926);
	GV.VarSet("iB", "*STRING SUPIMPA*");

	// Check their new types
	cout << endl << "Novo iA type: " << GV.VarGet_Type("iA");
	cout << endl << "Novo iB type: " << GV.VarGet_Type("iB");

	// Print out new values
	cout << endl << "Novo iA = fC*pi = " << GV.VarGet_Float("iA");
	cout << endl << "Novo iB: " << GV.VarGet_String("iB");

	// Access inexistent element
	cout << endl << "\n\nAcessando elemento inexistente:\nTipo: " << GV.VarGet("").type().name() << "\nValor: " << GV.VarGet_Int("") << endl;

}

