// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include "Main.h"


int main()
{


	GlobVar = GlobalVariables();
	UserEvents UsrEvt = UserEvents(GlobVar);
	TextParser TxtPar = TextParser();

	TEST_UserFunctionADD(UsrEvt);
	//TEST_UserEventsEventList(UsrEvt);

	//TEST_GlobalVariableSetGetType(GlobVar);

	/**
	TEST_TextParser(TxtPar);
	TEST_TextParser_PrintFile(TxtPar);
	TEST_TextParser_WordBlock(TxtPar);
	/**/

	//TEST_BoostAnyPTR();

	system("pause");

	return 0;
}

#pragma region Test Functions

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

	#pragma region Test UserEvents Class
	void TEST_UserFunctionADD(UserEvents &UsrEvt)
	{
		using std::endl;
		using std::cout;
		using std::cin;

		int A[2];
		int Result;
		std::string EventAlias = "ADD";

		cout << "Test User Event Choose Function with Add User Function Implemented" << endl;
		cout << "Enter an Integer A: ";
		cin >> A[0];
		cout << endl << "Enter another integer B: ";
		std::cin >> A[1];
		cout << endl;

		GlobVar.VarSet("A", A[0]);
		GlobVar.VarSet("B", A[1]);
		
		boost::any *Temp[2] = { GlobVar.VarGet_ptr("A"), GlobVar.VarGet_ptr("B") };
		int B[2] = { boost::any_cast<int>(*Temp[0]), boost::any_cast<int>(*Temp[1]) };

		UsrEvt.Choose(EventAlias, &B, &Result);

		cout << "A+B = " << Result << endl << endl;
		return;
	}

	void TEST_UserEventsEventList(UserEvents &UsrEvt)
	{
		using std::endl;
		using std::cout;
		using std::cin;

		UsrEvt.GlobalVar->VarSet("Test", "WOOOOO");
		UsrEvt.GlobalVar->VarSet("Name", "Pedro Mendonca");
		UsrEvt.GetEventList("D:/EP/EvtList.txt");

		for (unsigned int i = 0; i < UsrEvt.EventList.size(); i++)
		{
			cout << i << ": " << UsrEvt.EventList.at(i).EventName;
			//for (unsigned int j = 0; j < UsrEvt.EventList.at(i).EventParams.size(); j++)
			//{
			//	//cout << " // " << boost::any_cast<int>(UsrEvt.EventList.at(i).EventParams.at(j));
			//}
			cout << endl;
		}
		cout << endl << endl << "Contents of EventList(2): " << UsrEvt.EventList.at(2).EventName;
		cout << endl << "Contents of EventList(2,0): " << (boost::any_cast<std::string>(UsrEvt.EventList.at(2).EventParams.at(0)));
		//std::string* Test = (std::string*)GlobVar.VarGet_ptr("Name");
		boost::any* strPtr = (boost::any_cast<boost::any*>(UsrEvt.EventList.at(2).EventParams.at(1)));
		cout << endl << "Contents of EventList(2,1): " << (std::string)(boost::any_cast<const char*>(*strPtr)) << endl << endl;

		*strPtr = "Edited by pointer ;)";
		cout << "Editing by the pointer: " << GlobVar.VarGet_String("Name") << endl << endl;

		GlobVar.VarSet("Name", "Edited by GlobVar Obj");
		cout << "Editing by the GlobVar Obj: " << (std::string)(boost::any_cast<const char*>(*strPtr)) << endl << endl;
	}
	#pragma endregion


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
