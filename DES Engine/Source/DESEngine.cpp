// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#include "DESEngine.h"

DESE::DESEngine::DESEngine(SystemManager SystemManager) : SysMan(SystemManager)
{
	SysEvt_Collect.RegisterEvents(&SysMan);
}

DESE::DESEngine::~DESEngine()
{
}

void DESE::DESEngine::Simulation_Start(const std::string &Filename)
{
	PrintSysMsg("@SYS: Simulation_Start(" + Filename + ")\n", &SysMan, 12);
	EventList_Load(Filename);
	Simulation_Start();
}

// Starts the Simulation on the Currently loaded EventList
void DESE::DESEngine::Simulation_Start()
{
	// Clear Variables
	SysMan.UserVariables.ClearAllVariables();
	
	Print_AllSettings();
	Simulation_Loop();
	Simulation_End();
}

void DESE::DESEngine::Simulation_Loop()
{
	EventEntry NextEvent;

	while (true)
	{
		// Check Stop conditions
			if (SysMan.ShouldStop()) { return; }
		// Gets next event name and params
			NextEvent = SysMan.Event_List.getNextEvent();
		// Runs next event with it's corresponding params.
			SysMan.Event_Catalog.getEvent(NextEvent.Name)->Run(NextEvent.Params);
	} /// while
} /// Simulation_Loop

void DESE::DESEngine::Simulation_End()
{
	using std::cout; using std::endl;
	cout << "\n\nSimulation Ended. Reason: ";
	switch (SysMan.Status)
	{
	case Simulation_Halted_byEvent:
			cout << " Halted by Event" << endl;
	case Simulation_Halted_noMoreEvents:
			cout << " End of Event List" << endl;
	case Simulation_Failed:
		cout << " Simulation Failed" << endl;
	default:
		cout << " Unknown?" << endl;

	}
}

void DESE::DESEngine::Print_AllSettings()
{
	using std::cout; using std::endl;
	cout << "Engine current settings: " << endl;

	cout << "\tPrint System Commands: " << SysMan.Settings.Print_SystemCommands << endl;

	cout << "\tGOTO: Halt on Fail: " << SysMan.Settings.GoTo_HaltOnFail << endl;
	cout << "\tGOTO: Print: " << SysMan.Settings.GoTo_Print << endl;
	
	cout << "\tEvent List Size: " << SysMan.Event_List.size() << endl;
	cout << "-------------------------------------------" << endl;
}

// Returns an std::vector with the event list. EventList = {"add", {2, 3, "$var_C"}}
void DESE::DESEngine::EventList_Load(const std::string & Filename)
{
	// Get File lines and line count
	DESE::TextParser TxtPar(Filename);
	unsigned int fLineCount = TxtPar.GetLineCount();

	// Variables used in the loop
	std::string				 Line = "";
	std::vector<std::string> WordBlocks;
	std::string				 EventName;
	std::vector<boost::any>  EventParams;

	SysMan.Event_List.clear();

	// Loop Lines of File
	for (unsigned int i = 1; i <= fLineCount; i++)
	{
		Line = TxtPar.GetLine(i);
		TxtPar.GetWordBlocks(WordBlocks, Line, true); // Because of ExtractEventParameter, Append %s should be optional

		EventParams.clear();
		// Get event parameters by looping WordBlocks from 1 to size-1 (starts at 1 because 0 is event name)
		for (unsigned j = 1; j < WordBlocks.size(); j++)
		{
			// Extracts the next Event Parameter appropriately
			ExtractEventParameter(WordBlocks.at(j), EventParams);
		}

		// Get event name
		if (WordBlocks.size() > 0)
		{
			EventName = WordBlocks.at(0);
			SysMan.Event_List.push_back({ EventName, EventParams });
		}

	} /// for line looping

	if (SysMan.Settings.Print_SystemCommands)
	{
		PrintSysMsg("@SYS: EventList Loaded:\n", &SysMan, 11);
		PrintSysMsg("\t Event#\t EventName\t #Params\n", &SysMan, 11);
		for (unsigned int i = 0; i < SysMan.Event_List.size(); i++)
		{
			PrintSysMsg("\t " + std::to_string(i) + "\t " + SysMan.Event_List.at(i).Name + "\t\t " + std::to_string(SysMan.Event_List.at(i).Params.size()) + "\n", &SysMan, 3);
		}
	}

	return;
} /// EventList Load

// Extracts the corresponding Event Parameters
// Warning: "Ruins" the contents of WordBlock
void DESE::DESEngine::ExtractEventParameter(std::string & WordBlock, std::vector<boost::any>& EvtParams)
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
			} /// switch(CaseChar)

			EvtParams.push_back(Param);
			return;
		} /// else if (Wordblock.at(1) == '%')

	} /// if length > 2


	// If we reach this point of code that's because:
		// WordBlock.length < 2
		// OR WordBlock.at(1) != '%'; so it doesn't return from function
		// OR It isn't a variable; so it doesn't return from function
	// So we treat it as string:
	Param = std::string(WordBlock);
	EvtParams.push_back(Param);
	return;
} ///ExtractEventParam
