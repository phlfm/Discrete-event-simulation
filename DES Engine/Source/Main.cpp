// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#include "Main.h"

using namespace DESE;

int main()
{
	//std::string DropboxPath = "C:/Dropbox/Projects/Programming/DES Engine/DES Engine/Resource/Basic MVN Usage/"; // path do desktop
	std::string DropboxPath = "C:/Users/pedri/Dropbox/Projects/Programming/DES Engine/DES Engine/Resource/Basic MVN Usage/"; // path do laptop
	std::string File = DropboxPath + "ADD MalFormatado" + ".txt";
	

		SystemManager SysMan;
		SysMan.Settings.Print_SystemCommands = true;
		SysMan.Settings.GoTo_Print = true;

		ADDMALFORMATADO::UserEvent_Collection UserEvents(&SysMan);
		UserEvents.RegisterEvents(&SysMan);

		DESEngine DE = DESEngine(&SysMan);
		DE.Simulation_Start(File);
	
		//std::cout << "Caught untreated exception in main.cpp" << std::endl;
		//std::cout << ex.what() << std::endl << std::endl;


	system("pause");
	return 0;
}

/**
// Main para testes
int main()
{
	TEST_DESEngine();

	/// User Events
	//UserEvents UE = UserEvents();
	//TEST_UserEvents_ADD(UE);

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
/**/

// Tests GlobalVariables Class
void TEST_GlobalVariableSetGetType(DESE::GlobalVariables &GV)
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
	cout << "fC = " << GV.VarGet_casted<float>("fC") << "\n\n";

	// Change variable types (int -> float) (int -> string)
	GV.VarSet("iA", GV.VarGet_casted<float>("fC")*3.1415926);
	GV.VarSet("iB", "*STRING SUPIMPA*");

	// Check their new types
	cout << endl << "Novo iA type: " << GV.VarGet_Type("iA");
	cout << endl << "Novo iB type: " << GV.VarGet_Type("iB");

	// Print out new values
	cout << endl << "Novo iA = fC*pi = " << GV.VarGet_casted<float>("iA");
	cout << endl << "Novo iB: " << GV.VarGet_String("iB");

	// Access inexistent element
	cout << endl << "\n\nAcessando elemento inexistente:\nTipo: " << GV.VarGet("").type().name() << "\nValor: " << GV.VarGet_casted<int>("") << endl;

}

	// Makes TextParser ready for action
	void TEST_TextParser(TextParser &TP)
	{
		using std::endl;
		using std::cout;
		using std::cin;

		std::string Filename;
		while (true)
		{
			cout << "Enter filename: ";
			std::getline(cin >> std::ws, Filename);
			cout << endl << endl;
			TP.LoadLines(Filename);
		} 

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
