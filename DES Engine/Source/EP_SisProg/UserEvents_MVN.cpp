#include "UserEvents_MVN.h"
using std::cout;
using std::cin;
using std::endl;

template <typename I> std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
	static const char* digits = "0123456789ABCDEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i<hex_len; ++i, j -= 4)
		rc[i] = digits[(w >> j) & 0x0f];
	return "0x" + rc;
}

UserEvents_MVN::UserEvents_MVN() : UserEvents()
{
	BuildUFPAliasMap();
}

UserEvents_MVN::~UserEvents_MVN()
{
}

// If UserFunctions use the same alias as system functions, they will not be called.
// For this reason don't start user function aliases with @
void UserEvents_MVN::BuildUFPAliasMap()
{
	UserFunctionPointerMap_AddFunction("INITMVN",			&UserEvents_MVN::InitMVN );
	UserFunctionPointerMap_AddFunction("FILE_INPUT",		&UserEvents_MVN::FILE_INPUT);
	UserFunctionPointerMap_AddFunction("FILE_OUTPUT",		&UserEvents_MVN::FILE_OUTPUT );
	UserFunctionPointerMap_AddFunction("MEMDUMP_LOAD",		&UserEvents_MVN::MEMDUMP_LOAD );
	UserFunctionPointerMap_AddFunction("MEMDUMP",			&UserEvents_MVN::MEMDUMP );
	UserFunctionPointerMap_AddFunction("PRINTREG",			&UserEvents_MVN::PRINTREG);
	UserFunctionPointerMap_AddFunction("InstructionDecode",	&UserEvents_MVN::InstructionDecode);
	UserFunctionPointerMap_AddFunction("ADD",				&UserEvents_MVN::Add);
}

void UserEvents_MVN::Print(std::string Message, int OutputColor, int DefaultColor, bool IsInstruction)
{
	if ((IsInstruction && boost::any_cast<bool>(UserVariables.VarGet("Print_Instructions"))) || !IsInstruction)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, OutputColor);

		std::cout << Message;

		SetConsoleTextAttribute(hConsole, DefaultColor);
	}

	return;
	// Color codes:
	// DARK	1		2		3		4		5		6		7		 8
	//		Blue	Green	Cyan	Red		Purple	Gold	Whiteish Gray
	// LIGHT	9		10		11		12		13		14		15	
	//			Blue	Green	Cyan	Red		Purple	Yellow	White
	// 16 to ... = Same colors but with blue background
	// 16 = 10 in hexa = darkblue background + black font)
}

#pragma region User Functions

// User must modify void UserEvents::BuildUFPAliasMap()

void UserEvents_MVN::InitMVN(const std::vector<boost::any>& Parameters)
{
	Print("\n--------------------------------------------------\n\nInitializing MVN\n", 11);

	// Configure Opcode and Operand sizes in bytes (1 byte = 00 to FF)
	unsigned int SIZE_OPCODE = 1;
	unsigned int SIZE_OPERAND = 1;
	bool Print_Instructions = true;
	bool Dump_OnHaltOnly = true;

	unsigned int PCIncrement = SIZE_OPCODE + SIZE_OPERAND;
	unsigned int SIZE_Memory = 256 * SIZE_OPERAND; // Memory size in bytes
	unsigned int PC = 0;
	int AC = 0;
	unsigned int InputC = 0;
	unsigned int OutputC = 0;

	std::vector<unsigned char> Mem;
	Mem.reserve(SIZE_Memory);
	Mem.clear();
	Mem.assign(SIZE_Memory, 0);


	UserVariables.VarSet("SIZE_OPCODE", SIZE_OPCODE);
	UserVariables.VarSet("SIZE_OPERAND", SIZE_OPERAND);
	UserVariables.VarSet("Print_Instructions", Print_Instructions);
	UserVariables.VarSet("DumpHaltOnly", Dump_OnHaltOnly);
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
	Print("\tAC\t\t" + std::to_string(boost::any_cast<int>(UserVariables.VarGet("AC"))) + "\n", 3);
	Print("\tIC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("IC"))) + "\n", 3);
	Print("\tOC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("OC"))) + "\n", 3);
	Print("\tMEM.size()\t" + std::to_string(boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM")).size()) + "\n", 3);
	Print("MVN LOADED\n--------------------------------------------------\n\n", 11);
	return;
}

void UserEvents_MVN::FILE_INPUT(const std::vector<boost::any>& Parameters)
{
	UserVariables.VarSet("FILE_INPUT", Boost2String(Parameters.at(0)));
	Print("\tFILE_INPUT\t" + Boost2String(UserVariables.VarGet("FILE_INPUT")) + "\n", 3);
}

void UserEvents_MVN::FILE_OUTPUT(const std::vector<boost::any>& Parameters)
{
	UserVariables.VarSet("FILE_OUTPUT", Boost2String(Parameters.at(0)));
	Print("\tFILE_OUTPUT\t" + Boost2String(UserVariables.VarGet("FILE_OUTPUT")) + "\n", 3);
}

void UserEvents_MVN::MEMDUMP_LOAD(const std::vector<boost::any>& Parameters)
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
	if (Mem.size() < FileSize) { throw std::exception::exception("Memory not big enough to load MemoryDump"); }

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

void UserEvents_MVN::MEMDUMP(const std::vector<boost::any>& Parameters)
{
	if (boost::any_cast<bool>(UserVariables.VarGet("DumpHaltOnly")) == true)
	{
		if (UserVariables.VarGet_Int("$MVNHALT", 0, 0) == 0)
		{
			return;
		}
	}
	std::string Filename = Boost2String(Parameters.at(0));
	std::ofstream File(Filename, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

	// Checks for "fail" and "bad"
	if (!File) { return; }

	// Declare memory and buffer
	std::vector<unsigned char> Mem = boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM"));
	char* Buffer = new char[Mem.size()];

	// Copy memory into buffer
	for (unsigned int i = 0; i < Mem.size(); i++) { Buffer[i] = Mem.at(i); }

	// Write dump
	File.seekp(0, std::ios::beg);
	File.write(Buffer, Mem.size());
	File.close();

	Print("\t" + std::to_string(Mem.size()) + " bytes written to dump from memory (" + Filename + ")\n", 3);

	delete Buffer;

}

void UserEvents_MVN::MEMPRINT(const std::vector<boost::any>& Parameters)
{

}

void UserEvents_MVN::PRINTREG(const std::vector<boost::any>& Parameters)
{
	Print("\tPC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("PC"))) + "\n", 3);
	Print("\tAC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("AC"))) + "\n", 3);
	Print("\tIC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("IC"))) + "\n", 3);
	Print("\tOC\t\t" + std::to_string(boost::any_cast<unsigned int>(UserVariables.VarGet("OC"))) + "\n", 3);
}

void UserEvents_MVN::InstructionDecode(const std::vector<boost::any>& Parameters)
{
	// Retrieve MVN variables
	unsigned int SIZE_OPCODE = boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_OPCODE"));
	unsigned int SIZE_OPERAND = boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_OPERAND"));
	bool Print_Instructions = boost::any_cast<bool>(UserVariables.VarGet("Print_Instructions"));
	unsigned int PCIncrement = boost::any_cast<unsigned int>(UserVariables.VarGet("PCINCREMENT"));
	unsigned int SIZE_Memory = boost::any_cast<unsigned int>(UserVariables.VarGet("SIZE_MEMORY"));
	std::vector<unsigned char> Mem = boost::any_cast<std::vector<unsigned char>>(UserVariables.VarGet("MEM"));
	unsigned int PC = boost::any_cast<unsigned int>(UserVariables.VarGet("PC"));
	int AC = boost::any_cast<int>(UserVariables.VarGet("AC"));
	unsigned int InputC = boost::any_cast<unsigned int>(UserVariables.VarGet("IC"));
	unsigned int OutputC = boost::any_cast<unsigned int>(UserVariables.VarGet("OC"));
	std::string FileOUTPUT = Boost2String(UserVariables.VarGet("FILE_OUTPUT"));
	std::string FileINPUT = Boost2String(UserVariables.VarGet("FILE_INPUT"));
	std::ofstream FileOUT;
	std::ifstream FileIN;

	unsigned char* OPCODE = new unsigned char[SIZE_OPCODE];
	unsigned char* OPERAND = new unsigned char[SIZE_OPERAND];
	unsigned int OPERAND_uint = 0;

	// Fetch opcode and operand from memory
	// Opcode = PC + 0 to OPCODE_SIZE
	// Operand = PC + OPCODE_SIZE + 0 to OPERAND_SIZE
	for (unsigned int i = 0; i < SIZE_OPCODE; i++) { OPCODE[i] = Mem.at(PC + i); }
	for (unsigned int i = 0; i < SIZE_OPERAND; i++) { OPERAND[i] = Mem.at(PC + SIZE_OPCODE + i); }

	// Concat OPERAND[0] << 0 | OPERAND[1] << 8 | ... | OPERAND[n] << n*8
	// OPERAND[n] is shifted n*8 because char has 8 bits and we concat them with bitwise OR |
	// If OPERAND_SIZE is too big, it might not fit in an uint.
	for (unsigned int i = 0; i < SIZE_OPERAND; i++) {
		OPERAND_uint = OPERAND_uint | (OPERAND[i] << (8 * i));
	}
	// Now OPERAND_uint holds all the bytes of OPERAND[] concatenated

	// Switch / Decode instruction OPCODE... This needs to be changed for OPCODE and OPERAND bigger than 1 byte
	char* Buffer = nullptr;
	unsigned int TempAC = 0;
	unsigned int TempMem = 0;
	int BufferConcat = 0;
	unsigned int FileSize = 0;

	switch (OPCODE[0])
	{
		// JP - Inconditional Jump
	case 0x00:	PC = OPERAND_uint; Print("JP\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true);	break;
		// JZ - Jump if Zero
	case 0x10:	if (AC == 0) { PC = OPERAND_uint; Print("JZ T\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true); }
				else { PC += PCIncrement; Print("JZ F\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true); }	break;
				// JN - Jump if Negative
	case 0x20:	if (AC < 0) { PC = OPERAND_uint; Print("JN T\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true); }
				else { PC += PCIncrement; Print("JN F\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true); }	break;
				// LV - Load Value
	case 0x30: AC = (int)OPERAND_uint;  PC += PCIncrement; Print("LV\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// + - ADD
	case 0x40: AC += (int)Mem.at(OPERAND_uint); PC += PCIncrement; Print("ADD+\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// - - SUBTRACT
	case 0x50: AC -= (int)Mem.at(OPERAND_uint); PC += PCIncrement; Print("SUB-\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// * - MULTIPLY (Uses INT not float)
	case 0x60: AC *= (int)Mem.at(OPERAND_uint); PC += PCIncrement; Print("MUL*\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// / - DIVIDE (Uses INT not float)
	case 0x70: AC /= (int)Mem.at(OPERAND_uint); PC += PCIncrement; Print("DIV/\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// LD - Load from Memory
	case 0x80: AC = (int)Mem.at(OPERAND_uint); PC += PCIncrement; Print("LD\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true); break;
		// MM - Move to Memory
	case 0x90:
		TempAC = (unsigned int)AC;
		TempMem = 0;
		for (unsigned int i = 0; i < SIZE_OPERAND; i++)
		{
			TempMem = TempAC & 0xFF; // Gets the 8 LSB of TempAC
			Mem.at(OPERAND[SIZE_OPERAND - 1 - i]) = (unsigned char)TempMem;
			TempAC = TempAC >> 8; // Throws away 8 LSB of TempAC
		}
		PC += PCIncrement;
		Print("MM\tOP\t = " + n2hexstr(OPERAND_uint) + "\n", 3, 7, true);
		break;
		// SC - Subroutine Call
	case 0xA0:
		// OP aponta endereco da subrotina que comeca com JP XXXX
		// OP+OPCODE_SIZE armazena PC+PCincrementa que eh o end de volta da subrotina
		Mem.at(OPERAND_uint + SIZE_OPCODE) = PC + PCIncrement;

		PC = OPERAND_uint + PCIncrement;
		Print("SC\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true);
		break;
		// RS - Return from Subroutine
	case 0xB0:
		// OP aponta endereco da subrotina (JP EndDeVoltaDaSubRotina)
		PC = OPERAND_uint;
		Print("RS\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true);
		break;
		// HM - Halt Machine
	case 0xC0:
		UserVariables.VarSet("$MVNHALT", (int)Mem.at(OPERAND_uint));
		// A linha abaixo faz o HM printar o conteudo da memoria em OP
		Print("HM\t" + n2hexstr((int)Mem.at(OPERAND_uint)) + "\n", 3, 7, true);
		// A linha abaixo faz o HM printar o conteudo de OP
		//Print("HM\t" + n2hexstr(OPERAND_uint) + "\n", 3, 7, true);
		PC += PCIncrement;
		break;
		// GDAC - Get Data to AC
	case 0xD0:
		FileIN.open(FileINPUT, std::ifstream::in | std::ifstream::binary);

		// Checks for "fail" and "bad"
		if (!FileIN) { return; }

		FileIN.seekg(InputC);

		Buffer = new char[SIZE_OPERAND];
		FileIN.read(Buffer, SIZE_OPERAND);
		FileIN.close();

		BufferConcat = 0;
		for (unsigned int i = 0; i < SIZE_OPERAND; i++) { BufferConcat = BufferConcat | (Buffer[SIZE_OPERAND - 1 - i] << (8 * i)); }

		//Acum = GD
		AC = BufferConcat;

		InputC += SIZE_OPERAND;
		Print("GD\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true);

		// Clear memory allocation
		delete Buffer;

		PC += PCIncrement;
		break;
		// GS - Get data Set counter
	case 0xD1:	InputC = Mem.at(OPERAND_uint); PC += PCIncrement; Print("GS\tIC\t = " + n2hexstr(InputC) + "\n", 3, 7, true); break;
		// GDM - Get Data to Mem[AC]
	case 0xD2:
		FileIN.open(FileINPUT, std::ifstream::in | std::ifstream::binary);

		// Checks for "fail" and "bad"
		if (!FileIN) { return; }

		FileIN.seekg(InputC);

		Buffer = new char[SIZE_OPERAND];
		FileIN.read(Buffer, SIZE_OPERAND);
		FileIN.close();

		BufferConcat = 0;
		for (unsigned int i = 0; i < SIZE_OPERAND; i++) { BufferConcat = BufferConcat | (Buffer[SIZE_OPERAND - 1 - i] << (8 * i)); }

		//Memory[AC] = GD
		Mem.at(AC) = BufferConcat;

		InputC += SIZE_OPERAND;
		Print("GD\tMem[AC]\t = " + n2hexstr((int)Mem.at(AC)) + "\n", 3, 7, true);

		// Clear memory allocation
		delete Buffer;

		PC += PCIncrement;
		break;
		// EOFI - If input EOF jump to OP
	case 0xDF:
		FileIN.open(FileINPUT, std::ifstream::in | std::ifstream::binary);

		// Checks for "fail" and "bad"
		if (!FileIN) { return; }

		//Get file size

		FileIN.seekg(0, std::ios::beg);
		FileSize = (unsigned int)FileIN.tellg();
		FileIN.seekg(0, std::ios::end);
		FileSize = (unsigned int)FileIN.tellg() - FileSize;

		if (InputC >= FileSize - 1)
		{
			PC = OPERAND_uint; Print("EOF T\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true);
		}
		else
		{
			PC += PCIncrement; Print("EOF F\tPC\t = " + n2hexstr(PC) + "\n", 3, 7, true);
		}	break;
		break;

		// PD - Put Data AC into File
	case 0xE0:
		FileOUT.open(FileOUTPUT, std::ofstream::in | std::ofstream::out | std::ofstream::binary);
		Buffer = new char[SIZE_OPERAND];

		TempAC = (unsigned int)AC;
		TempMem = 0;
		for (unsigned int i = 0; i < SIZE_OPERAND; i++)
		{
			TempMem = TempAC & 0xFF; // Gets the 8 LSB of TempAC
			Buffer[SIZE_OPERAND - 1 - i] = (unsigned char)TempMem;
			TempAC = TempAC >> 8; // Throws away 8 LSB of TempAC
		}

		// Checks for "fail" and "bad"
		if (!FileOUT) { return; }

		// Write Buffer
		FileOUT.seekp(OutputC);
		FileOUT.write(Buffer, SIZE_OPERAND);
		FileOUT.close();

		OutputC += SIZE_OPERAND;
		Print("PD\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true);

		delete Buffer;

		PC += PCIncrement;
		break;
		// PS - Put data Set counter
	case 0xE1:	OutputC = Mem.at(OPERAND_uint); PC += PCIncrement; Print("PS\tOC\t = " + n2hexstr(OutputC) + "\n", 3, 7, true); break;
		// PDM - Put Data Mem[AC] into File
	case 0xE2:
		FileOUT.open(FileOUTPUT, std::ofstream::in | std::ofstream::out | std::ofstream::binary);
		Buffer = new char[SIZE_OPERAND];

		TempAC = Mem.at((unsigned int)AC);
		TempMem = 0;
		for (unsigned int i = 0; i < SIZE_OPERAND; i++)
		{
			TempMem = TempAC & 0xFF; // Gets the 8 LSB of TempAC
			Buffer[SIZE_OPERAND - 1 - i] = (unsigned char)TempMem;
			TempAC = TempAC >> 8; // Throws away 8 LSB of TempAC
		}

		// Checks for "fail" and "bad"
		if (!FileOUT) { return; }

		// Write Buffer
		FileOUT.seekp(OutputC);
		FileOUT.write(Buffer, SIZE_OPERAND);
		FileOUT.close();

		OutputC += SIZE_OPERAND;
		Print("PD\tAC\t = " + n2hexstr(AC) + "\n", 3, 7, true);

		delete Buffer;

		PC += PCIncrement;
		break;
		// OS - Operating System call
	case 0xF0:
		PC += PCIncrement; Print("OS\n", 3, 7, true);
		break;
	case 0xF1:
		PC += PCIncrement; system("pause");
		break;

	default:
		break;
	}


	UserVariables.VarSet("PC", PC);
	UserVariables.VarSet("AC", AC);
	UserVariables.VarSet("IC", InputC);
	UserVariables.VarSet("OC", OutputC);
	UserVariables.VarSet("MEM", Mem);

	return;
}

void UserEvents_MVN::Add(const std::vector<boost::any> &Parameters)
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

