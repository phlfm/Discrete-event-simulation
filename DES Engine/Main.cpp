// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include "Main.h"


int main()
{

	/// User Events
	UserEvents UE = UserEvents();
	TEST_UserEvents_ADD(UE);

	/// Global Variable
	//GlobalVariables GlobVar = GlobalVariables();
	//TEST_GlobalVariableSetGetType(GlobVar);

	/// Text Parser
	//TextParser TxtPar = TextParser();	
	//TEST_TextParser(TxtPar);
	//TEST_TextParser_PrintFile(TxtPar);
	//TEST_TextParser_WordBlock(TxtPar);

	/// Misc
	//TEST_BoostAnyPTR();

	system("pause");

	return 0;
}

#pragma region Test Functions

void TEST_UserEvents_ADD(UserEvents &UE)
{
	using std::endl;
	using std::cout;
	using std::cin;


	int A[2];

	//Get Input
	cout << "Enter an Integer A: ";
	cin >> A[0];
	cout << endl << "Enter another integer B: ";
	cin >> A[1];
	cout << endl;

	//UE.Event.Name = "ADD";
	std::vector<boost::any> Param;
	Param.push_back(A[0]);
	Param.push_back(A[1]);
	//UE.Event.Params = Param;
	UE.Event = { "ADD", Param };
	UE.Choose();

	cout << endl << "A+B = " << UE.UserVariables.VarGet_Int("add");
}

void TEST_BoostAnyPTR()
{
	using std::cout;
	using std::endl;

	boost::any Variable = 0;
	boost::any *Varptr = &Variable;
	cout << "Variable type: " << Variable.type().name() << " contains: " << boost::any_cast<int>(Variable) << endl << endl;

	*Varptr = "Pedro";
	cout << "Variable by PTR below:\nVariable type: " << Variable.type().name() << " contains: " << (std::string)(boost::any_cast<const char*>(Variable)) << endl << endl;

	Variable = 1000;
	int *ptrInt = boost::any_cast<int>(&Variable);
	cout << "*ptrInt = " << *ptrInt << "\nptrInt = " << ptrInt << "\n(int)&Variable = " << boost::any_cast<int>(&Variable) << "\n(int)*Varptr = " << boost::any_cast<int>(*Varptr) <<
		"\n(int)Varptr = " << boost::any_cast<int*>(Varptr) << endl << endl;

	*ptrInt = 1111;
	cout << "*ptrInt = " << *ptrInt << "\nptrInt = " << ptrInt << "\n(int)&Variable = " << boost::any_cast<int>(&Variable) << "\n(int)*Varptr = " << boost::any_cast<int>(*Varptr) <<
		"\n(int)Varptr = " << boost::any_cast<int*>(Varptr) << endl << endl;



	Variable = "Pedro";
	cout << "Variable = " << (std::string)(boost::any_cast<const char*>(Variable)) << "\nptrInt contains: " << ptrInt << "\n*ptrInt contains : " << *ptrInt << endl << endl;

	return;
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

	#pragma region Test Text Parser
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
		} while (!(TP.LoadLines(Filename) == 0));

	}

	void TEST_TextParser_PrintFile(TextParser &TP)
	{
		using std::endl;
		using std::cout;

		std::string Filename = TP.GetFilename();
		cout << "Printing File: " << TP.GetFilename() << endl;
		cout << "Line number: " << TP.GetLineCount() << endl;
		cout << "--------------- BOF ---------------\n\n";

		for (unsigned int i = 1; i <= TP.GetLineCount(); i++)
		{
			cout << i << ": " << TP.GetLine(i) << endl;
		}

		cout << "\n\n--------------- EOF ---------------\n\n\n";
	}

	void TEST_TextParser_WordBlock(TextParser &TP)
	{
		using std::endl;
		using std::cout;

		std::vector<std::string> WordBlock;

		cout << "\n\n--------------- Word Block ---------------\n\n\n";

		for (unsigned int i = 1; i <= TP.GetLineCount(); i++)
		{
			TP.GetWordBlocks(WordBlock, TP.GetLine(i), true);

			for (unsigned int j = 0; j < WordBlock.size(); j++)
			{
				cout << i << "/" << j << ": " << WordBlock.at(j) << endl;
			}
			cout << endl;
		}

		cout << "\n\n--------------- Word Block End ---------------\n\n\n";
	}
	#pragma endregion

#pragma endregion Functions to test different Classes
