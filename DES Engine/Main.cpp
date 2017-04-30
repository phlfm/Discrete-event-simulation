// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include "Main.h"


int main()
{


	UserEvents UsrEvt = UserEvents();
	GlobalVariables GlobVar = GlobalVariables();
	TextParser TxtPar = TextParser();

	TEST_UserFunctionADD(UsrEvt);

	//TEST_GlobalVariableSetGetType(GlobVar);

	/**
	TEST_TextParser(TxtPar);
	TEST_TextParser_PrintFile(TxtPar);
	TEST_TextParser_WordBlock(TxtPar);
	/**/


	system("pause");

	return 0;
}

#pragma region Test Functions

// Tests UserEvents Class
void TEST_UserFunctionADD(UserEvents &UsrEvt)
{
	using std::endl;
	using std::cout;
	using std::cin;

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

// Tests GlobalVariables Class
void TEST_GlobalVariableSetGetType(GlobalVariables &GV)
{
	using std::endl;
	using std::cout;
	using std::cin;

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

// Tests TextParser Class
// Makes TextParser ready for action
void TEST_TextParser(TextParser &TP)
{
	using std::endl;
	using std::cout;
	using std::cin;

	std::string Filename;
	do
	{
		cout << "Enter filename: ";
		std::getline(cin >> std::ws, Filename);
		cout << endl << endl;
	} while (!(TP.FileLoadLines(Filename) == 0));

}

void TEST_TextParser_PrintFile(TextParser &TP)
{
	using std::endl;
	using std::cout;
	
	std::string Filename = TP.GetFilename();
	cout << "Printing File: " << TP.GetFilename() << endl;
	cout << "Line number: " << TP.FileLineCount() << endl;
	cout << "--------------- BOF ---------------\n\n";
	
	for (unsigned int i = 1; i <= TP.FileLineCount(); i++)
	{
		cout << i << ": " << TP.FileGetLine(i) << endl;
	}

	cout << "\n\n--------------- EOF ---------------\n\n\n";
}

void TEST_TextParser_WordBlock(TextParser &TP)
{
	using std::endl;
	using std::cout;
	
	std::vector<std::string> WordBlock;

	cout << "\n\n--------------- Word Block ---------------\n\n\n";

	for (unsigned int i = 1; i <= TP.FileLineCount(); i++)
	{
		TP.GetWordBlocks(WordBlock, TP.FileGetLine(i), true);

		for (unsigned int j = 0; j < WordBlock.size(); j++)
		{
			cout << i << "/" << j << ": " << WordBlock.at(j) << endl;
		}
		cout << endl;
	}

	cout << "\n\n--------------- Word Block End ---------------\n\n\n";
}


#pragma endregion Functions to test different Classes
