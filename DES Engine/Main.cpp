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
	cout << endl << boost::any_cast<std::string>(GV.VarGet("Nombre")) << ", A/B is:";
	cout << endl << "fC = " << boost::any_cast<float>(GV.VarGet("fC")) << "\n\n";

	// Change variable types (int -> float) (int -> string)
	GV.VarSet("iA", (float)(boost::any_cast<float>(GV.VarGet("fC"))*3.1415926));
	GV.VarSet("iB", (std::string)"*STRING SUPIMPA*");

	// Check their new types
	cout << endl << "Novo iA type: " << GV.VarGet_Type("iA");
	cout << endl << "Novo iB type: " << GV.VarGet_Type("iB");

	// Print out new values
	cout << endl << "Novo iA = iC*pi = " << boost::any_cast<float>(GV.VarGet("iA"));
	cout << endl << "Novo iB: " << boost::any_cast<std::string>(GV.VarGet("iB"));

	// Access inexistent element
	cout << endl << "Acessando elemento inexistente: TIPO:" << GV.VarGet("!@#", -1.2345).type().name() << "\nValor: " << boost::any_cast<double>(GV.VarGet("!@#", -1.2345)) << endl;

}

