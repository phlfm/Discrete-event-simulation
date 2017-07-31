// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2017

#include "DESEngine.h"

DESEngine::DESEngine()
{
	GVar_EventLabels = GlobalVariables();
	UsrEvt = UserEvents();

	BuildSystemEventsAlias();
}

DESEngine::~DESEngine()
{
}

// Returns an std::vector with the event list. EventList = {"add", {2, 3, "$var_C"}}
void DESEngine::EventList_Load(const std::string & Filename)
{
	// Get File lines and line count
	TxtPar = TextParser(Filename);
	unsigned int fLineCount = TxtPar.GetLineCount();
	
	// Variables used in the loop
	std::string				 Line = "";
	std::vector<std::string> WordBlocks;
	std::string				 EventName;
	std::vector<boost::any>  EventParams;
	
	EventList.clear();
	
	// Loop Lines of File
	for (unsigned int i = 1; i <= fLineCount; i++)
	{
		Line = TxtPar.GetLine(i);
		TxtPar.GetWordBlocks(WordBlocks, Line, true); // Because of how ExtractEventParameter, Append %s should be optional
	
		EventParams.clear();
		// Get event parameters by looping WordBlocks from 1 to size-1
		for (unsigned j = 1; j < WordBlocks.size(); j++)
		{
			// Extracts the next Event Parameter appropriately
			ExtractEventParameter(WordBlocks.at(j), EventParams);
		}
	
		// Get event name
		if (WordBlocks.size() > 0)
		{
			EventName = WordBlocks.at(0);
			EventList.push_back({ EventName, EventParams });
		}
	
	}
	
	//Deconstruct TxtPar??
	if (PrintSystemCommands)
	{
		PrintSYS("@SYS: EventList Loaded:\n", 11);
		PrintSYS("\t Event#\t EventName\t #Params\n", 11);
		for (unsigned int i = 0; i < EventList.size(); i++)
		{
			PrintSYS("\t " + std::to_string(i) + "\t " + EventList.at(i).Name + "\t\t " + std::to_string(EventList.at(i).Params.size()) + "\n", 3);
		}
	}

	return;
}

void DESEngine::Event_Select(const EventWithParams & Event)
{

// Call system event
	if (Event.Name.at(0) == '@')
	{
		std::string SystemEvent_Name = Event.Name;
		SystemEvent_Name.erase(0, 1); // Removes starting @
		
		std::string SystemEvent_Param = "";
		if (Event.Params.size() > 0) { SystemEvent_Param = Boost2String(Event.Params.at(0)); }

		// Call system event
		try
		{
			(this->*SystemFunctionPointerMap.at(SystemEvent_Name))(SystemEvent_Param);
		}
		catch (const std::out_of_range e)
		{
			throw std::exception::exception("User Event starting with @ or unknown System Function. Is the engine up to date?");
		}
	}
// Call user event
	else
	{
		UsrEvt.Event = { Event.Name, Event.Params };
		UsrEvt.Choose();
		// TODO Check if Event.Name = "@NEWEVENT" where params = list of events
	}
}

#pragma region System Functions

// Loads a NEW EventList and calls Simulation_Start()
bool DESEngine::Simulation_Start(const std::string &Filename)
{
	PrintSYS("@SYS: Simulation_Start(" + Filename + ")\n", 12);
	EventList_Load(Filename);

	return Simulation_Start();
}

// Starts the Simulation on the Currently loaded EventList
bool DESEngine::Simulation_Start()
{
	PrintSYS("@SYS: Simulation_Start\n", 12);
	// Clear Variables
	if (PurgeUserVariablesOnStart)
	{
		UsrEvt.UserVariables.ClearAllVariables();
		PrintSYS("@SYS: User Variables Purged\n", 12);
	}
	GVar_EventLabels.ClearAllVariables();

	EventPointer = EntryPoint;

	Simulation_Loop();
			
	return Halted;
}

void DESEngine::Simulation_Restart(const std::string &Filename)
{
	DESEngine::Simulation_Start(Filename);
	return;
}

void DESEngine::SysFct_HALT(const std::string &HaltTestVariable)
{
	if (UsrEvt.UserVariables.VarExists(HaltTestVariable))
	{
		int HaltTest = UsrEvt.UserVariables.VarGet_Int(HaltTestVariable, 0, 0);
		if (HaltTest != 0)
		{
			PrintSYS("@SYS: HALTED\n", 12);
			Halted = true;
		}
		else
		{
			if (PrintHaltFailed) { PrintSYS("@SYS: HALT TEST (" + std::to_string(HaltTest) + ")\n"); }
		}
	}
	else {
		if (PrintHaltFailed) { PrintSYS("@SYS: HALT TEST VARIABLE NOT FOUND (" + HaltTestVariable + ")\n"); }
	}

	return;
}

// Sets the label to current EventPointer.
// If two label names collide, only the first is kept
void DESEngine::SysFct_LABEL(const std::string &Label)
{
	if (!GVar_EventLabels.VarExists(Label))
	{
		GVar_EventLabels.VarSet(Label, EventPointer);
		PrintSYS("@SYS: New Label: " + Label + " @ Event: " + std::to_string(EventPointer) + "\n");
	}
	return;

}

// If the label is set, puts EventPointer to Label+1
void DESEngine::SysFct_GOTO(const std::string &Label)
{
	EventPointer = GVar_EventLabels.VarGet_uInt(Label);
	if (PrintGoto) { PrintSYS("@SYS: GOTO Label: " + Label + " @ Event: " + std::to_string(EventPointer) + "\n"); }
	return;
}

#pragma endregion Implementation of System Functions


void DESEngine::Simulation_Loop()
{
	while (EventPointer < EventList.size())
	{
		if (Halted) { return; }

		Event_Select(EventList.at(EventPointer));

		EventPointer++;
	}

	return;
}

void DESEngine::BuildSystemEventsAlias()
{
	SystemFunctionPointerMap.insert({ "HALT", &DESEngine::SysFct_HALT });
	SystemFunctionPointerMap.insert({ "LABEL", &DESEngine::SysFct_LABEL });
	SystemFunctionPointerMap.insert({ "@", &DESEngine::SysFct_LABEL }); //@@ also serves as label
	SystemFunctionPointerMap.insert({ "GOTO", &DESEngine::SysFct_GOTO });

	// Useful for iterative calculations with PurgeUserVariablesOnStart = False and EntryPoint
	SystemFunctionPointerMap.insert({ "RESTART", &DESEngine::Simulation_Restart });
	SystemFunctionPointerMap.insert({ "START", &DESEngine::Simulation_Restart });

	PrintSYS("@SYS: SystemFunctionPointerMap OK!\n", 12);
}

// Extracts the corresponding Event Parameters
// Warning: "Ruins" the contents of WordBlock
void DESEngine::ExtractEventParameter(std::string & WordBlock, std::vector<boost::any>& EvtParams)
{
	// Pre-Parameter Identifiers:
		// s%, i%, l%, f%, d%
		// string, int, long, float, double
		// s% is optional because it's the default action

	boost::any Param;

	if (WordBlock.length() > 2)
	{
		// If it starts with $ it's a GlobalVariable
		if (WordBlock.at(0) == '$')
		{
			Param = WordBlock;
		}
		// If NOT GlobalVar and second char = '%' --> cast appropriate type
		else if (WordBlock.at(1) == '%')
		{
			char CaseChar = WordBlock.at(0);

			switch (CaseChar)
			{
			case 'i':
				WordBlock.erase(0, 2); // Erases the identifier  i%
				Param = std::stoi(WordBlock);
				break;
			case 'l':
				WordBlock.erase(0, 2); // Erases the identifier  l%
				Param = std::stol(WordBlock);
				break;
			case 'f':
				WordBlock.erase(0, 2); // Erases the identifier  f%
				Param = std::stof(WordBlock);
				break;
			case 'd':
				WordBlock.erase(0, 2); // Erases the identifier  d%
				Param = std::stod(WordBlock);
				break;
			case 's':
				WordBlock.erase(0, 2); // Erases the identifier  s%
				Param = std::string(WordBlock);
				break;
			default:
				// If it doesn't have a pre-param-identifier treat as string
				Param = std::string(WordBlock);
				break;
			}

			EvtParams.push_back(Param);
			return;
		}

	}


	// If we reach this point of code that's because:
		// WordBlock.length < 2
		// OR WordBlock.at(1) != '%'; so it doesn't return from function
		// OR It isn't a variable; so it doesn't return from function
	// So we treat it as string:
	Param = std::string(WordBlock);
	EvtParams.push_back(Param);
	return;
}

std::string DESEngine::Boost2String(const boost::any & Parameter)
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

void DESEngine::PrintSYS(const char * Message, int OutputColor, int DefaultColor)
{

	if (PrintSystemCommands)
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

void DESEngine::PrintSYS(std::string Message, int OutputColor, int DefaultColor)
{

	if (PrintSystemCommands)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, OutputColor);

		std::cout << Message;

		SetConsoleTextAttribute(hConsole, DefaultColor);

		// Color codes:
		// DARK	1		2		3		4		5		6		7		 8
		//		Blue	Green	Cyan	Red		Purple	Gold	Whiteish Gray
		// LIGHT	9		10		11		12		13		14		15	
		//			Blue	Green	Cyan	Red		Purple	Yellow	White
		// 16 to ... = Same colors but with blue background
		// 16 = 10 in hexa = darkblue background + black font)

	}

	return;
}
