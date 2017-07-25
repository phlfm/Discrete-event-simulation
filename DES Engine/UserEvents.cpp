// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"
using std::cout;
using std::cin;
using std::endl;


// Class Constructor
UserEvents::UserEvents()
{
	UserVariables = GlobalVariables();
	BuildUFPAliasMap();
}

// Class Destructor
UserEvents::~UserEvents()
{
	
}

// Select which function(parameters) to call
// Returns 0 = UserFunction Found, -1 and exception if no function found
int UserEvents::Choose()
{
	try
	{
		(this->*UserFunctionPointerAliasMap.at(Event.Name))(Event.Params);
		return 0;
	}
	catch (const std::out_of_range e)
	{
		throw std::exception::exception("Unknown User Event");
		return -1;
	}
}

bool const UserEvents::IsParamVariable(const boost::any & Parameter)
{
	std::string ParamStr = Boost2String(Parameter);
	
	if (ParamStr == "") { return false; }
	// If we reach here, that means Parameter was cast into string
	if (ParamStr.at(0) == '$') { return true; }
	return false;
}

std::string UserEvents::Boost2String(const boost::any & Parameter)
{
	std::string ParamStr;

	// Convert Parameter to std::string
	try
	{
		ParamStr = (std::string)(boost::any_cast<const char*>(Parameter));
	}
	catch (const boost::bad_any_cast e)
	{
		try
		{
			ParamStr = boost::any_cast<std::string>(Parameter);
		}
		catch (const boost::bad_any_cast e)
		{
			return "";
		}
	}

	return ParamStr;
}

void UserEvents::Print(std::string Message, int OutputColor, int DefaultColor)
{

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, OutputColor);

		std::cout << Message;

		SetConsoleTextAttribute(hConsole, DefaultColor);


	return;
	// Color codes:
	// DARK	1		2		3		4		5		6		7		 8
	//		Blue	Green	Cyan	Red		Purple	Gold	Whiteish Gray
	// LIGHT	9		10		11		12		13		14		15	
	//			Blue	Green	Cyan	Red		Purple	Yellow	White
	// 16 to ... = Same colors but with blue background
	// 16 = 10 in hexa = darkblue background + black font)
}

// Builds the UserFunctionPointerAliasMap
void UserEvents::BuildUFPAliasMap()
{
	// If UserFunctions use the same alias as system functions, they will not be called.
	// For this reason don't start user function aliases with @

	// Add user functions below:
	UserFunctionPointerAliasMap.insert({ "INITMVN",				&UserEvents::InitMVN });
	UserFunctionPointerAliasMap.insert({ "FILE_INPUT",			&UserEvents::FILE_INPUT });
	UserFunctionPointerAliasMap.insert({ "FILE_OUTPUT",			&UserEvents::FILE_OUTPUT });
	UserFunctionPointerAliasMap.insert({ "MEMDUMP_LOAD",		&UserEvents::MEMDUMP_LOAD });
	UserFunctionPointerAliasMap.insert({ "MEMDUMP",				&UserEvents::MEMDUMP });
	UserFunctionPointerAliasMap.insert({ "PRINTREG",			&UserEvents::PRINTREG });
	UserFunctionPointerAliasMap.insert({ "InstructionDecode",	&UserEvents::InstructionDecode });


	UserFunctionPointerAliasMap.insert({ "ADD", &UserEvents::Add });

}

#pragma region User Functions

// User must modify void UserEvents::BuildUFPAliasMap()

void UserEvents::InitMVN(const std::vector<boost::any>& Parameters)
{
	Print("\n--------------------------------------------------\n\nInitializing MVN\n", 11);

	// Configure Opcode and Operand sizes in bytes (1 byte = 00 to FF)
	unsigned int SIZE_OPCODE = 1;
	unsigned int SIZE_OPERAND = 1;

	unsigned int PCIncrement = SIZE_OPCODE + SIZE_OPERAND;
	unsigned int SIZE_Memory = 256*SIZE_OPERAND; // Memory size in bytes
	unsigned int PC = 0;
	unsigned int AC = 0;
	unsigned int InputC = 0;
	unsigned int OutputC = 0;

	std::vector<unsigned char> Mem;
	Mem.reserve(SIZE_Memory);
	Mem.clear();
	Mem.assign(SIZE_Memory, 0);


	UserVariables.VarSet("SIZE_OPCODE", SIZE_OPCODE);
	UserVariables.VarSet("SIZE_OPERAND", SIZE_OPERAND);
	UserVariables.VarSet("PCINCREMENT", PCIncrement);
	UserVariables.VarSet("SIZE_MEMORY", SIZE_Memory);
	UserVariables.VarSet("PC", PC);
	UserVariables.VarSet("AC", AC);
	UserVariables.VarSet("IC", InputC);
	UserVariables.VarSet("OC", OutputC);
	UserVariables.VarSet("MEM", Mem);
	
	Print("\tSIZE_OPCODE\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_OPERAND"))) + "\n", 3);
	Print("\tSIZE_OPERAND\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_OPERAND"))) + "\n", 3);
	Print("\tPCINCREMENT\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("PCINCREMENT"))) + "\n", 3);
	Print("\tSIZE_MEMORY\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_MEMORY"))) + "\n", 3);
	Print("\tPC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("PC"))) + "\n", 3);
	Print("\tAC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("AC"))) + "\n", 3);
	Print("\tIC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("IC"))) + "\n", 3);
	Print("\tOC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("OC"))) + "\n", 3);
	Print("\tMEM.size()\t" + std::to_string(boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM")).size()) + "\n", 3);
	Print("MVN LOADED\n--------------------------------------------------\n\n", 11);
	return;
}

void UserEvents::FILE_INPUT(const std::vector<boost::any>& Parameters)
{
	UserVariables.VarSet("FILE_INPUT", Boost2String(Parameters.at(0)));
	Print("\tFILE_INPUT\t" + Boost2String(UserVariables.VarGet("FILE_INPUT")) + "\n", 3);
}

void UserEvents::FILE_OUTPUT(const std::vector<boost::any>& Parameters)
{
	UserVariables.VarSet("FILE_OUTPUT", Boost2String(Parameters.at(0)));
	Print("\tFILE_OUTPUT\t" + Boost2String(UserVariables.VarGet("FILE_OUTPUT")) + "\n", 3);
}

void UserEvents::MEMDUMP_LOAD(const std::vector<boost::any>& Parameters)
{
	std::string Filename = Boost2String(Parameters.at(0));
	std::ifstream File(Filename, std::ifstream::in | std::ifstream::binary);

	// Checks for "fail" and "bad"
	if (!File) { return; }

	//Get file size
	unsigned int FileSize = 0;

	File.seekg(0, std::ios::beg);
	FileSize = (unsigned int)File.tellg();
	File.seekg(0, std::ios::end);
	FileSize = (unsigned int)File.tellg() - FileSize;
	File.seekg(0, std::ios::beg);

	// Load Memory
	std::vector<unsigned char> Mem = boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM"));

	// Make sure dump fits in current memory allocation
	if (Mem.size() < FileSize)	{ throw std::exception::exception("Memory not big enough to load MemoryDump"); }

	// Read contents of MemoryDump
	char* Buffer = new char[FileSize];
	File.read(Buffer, FileSize);
	File.close();

	// Copy buffer into memory
	for (unsigned int i = 0; i < FileSize; i++) { Mem.at(i) = Buffer[i]; }

	UserVariables.VarSet("MEM", Mem);
	Print("\t" + std::to_string(FileSize) + " bytes copied from dump to memory (" + Filename + ")\n", 3);

	// Clear memory allocation
	delete Buffer;
}

void UserEvents::MEMDUMP(const std::vector<boost::any>& Parameters)
{
	std::string Filename = Boost2String(Parameters.at(0));
	std::ofstream File(Filename, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

	// Checks for "fail" and "bad"
	if (!File) { return; }

	// Declare memory and buffer
	std::vector<unsigned char> Mem = boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM"));
	char* Buffer = new char[Mem.size()];

	// Copy memory into buffer
	for (unsigned int i = 0; i < Mem.size(); i++) {Buffer[i] = Mem.at(i); }

	// Write dump
	File.seekp(0, std::ios::beg);
	File.write(Buffer, Mem.size());
	File.close();

	Print("\t" + std::to_string(Mem.size()) + " bytes written to dump from memory (" + Filename + ")\n", 3);

	delete Buffer;

}

void UserEvents::MEMPRINT(const std::vector<boost::any>& Parameters)
{

}

void UserEvents::PRINTREG(const std::vector<boost::any>& Parameters)
{
	Print("\tPC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("PC"))) + "\n", 3);
	Print("\tAC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("AC"))) + "\n", 3);
	Print("\tIC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("IC"))) + "\n", 3);
	Print("\tOC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("OC"))) + "\n", 3);
}

void UserEvents::InstructionDecode(const std::vector<boost::any>& Parameters)
{

}

void UserEvents::Add(const std::vector<boost::any> &Parameters)
{
	int A;
	if (IsParamVariable(Parameters.at(0)))
	{
		A = UserVariables.VarGet_Int(Boost2String(Parameters.at(0)));
	}
	else
	{
		A = boost::any_cast<int>(Parameters.at(0));
	}

	int B;
	if (IsParamVariable(Parameters.at(1)))
	{
		B = UserVariables.VarGet_Int(Boost2String(Parameters.at(1)));
	}
	else
	{
		B = boost::any_cast<int>(Parameters.at(1));
	}

	UserVariables.VarSet(Boost2String(Parameters.at(2)), A + B);
	cout << Boost2String(Parameters.at(2)) << " = " << A << " + " << B << " = " << A + B << endl;
	if (A + B > 5) { UserVariables.VarSet("$UserHalt", 1); }
	return;
}


#pragma endregion Implementation of User Functions

/* Text File Symbols

@	System Commands
//	Comment
$	Variable
"	Delimits strings (multi lines are not supported)
\" \\
i%, l%, u%, f%, d%, (optional) s%	determines the parameter type
If parameter type is not determined, treat as string
Each line should be:
COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
*/
/**/