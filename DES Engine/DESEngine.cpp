// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "DESEngine.h"

DESEngine::DESEngine()
{
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
	return;
}

void DESEngine::Event_Select(const EventWithParams & Event)
{

// Call system event
	if (Event.Name.at(0) == '@')
	{
		std::string SystemEvent_Name = Event.Name;
		SystemEvent_Name.erase(0, 1); // Removes starting @
		
		std::string SystemEvent_Param;

	// Convert Event.Params to std::string
		try
		{
			SystemEvent_Param = boost::any_cast<std::string>(Event.Params);
		}
		catch (const boost::bad_any_cast e)
		{
			try
			{
				SystemEvent_Param = (std::string)(boost::any_cast<const char*>(Event.Params));
			}
			catch (const boost::bad_any_cast e)
			{
				return;
			}
		}
	// End Conversion

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
	}
}

#pragma region System Functions

bool DESEngine::Simulation_Start(const std::string &Filename)
{
	// Clear Variables
	if (PurgeUserVariablesOnStart) { UsrEvt.UserVariables.ClearAllVariables(); }
	GVar_EventLabels.ClearAllVariables();

	EventPointer = EntryPoint;

	EventList_Load(Filename);

	Simulation_Loop();
			
	return Halted;
}

void DESEngine::Simulation_Restart(const std::string &Filename)
{
	DESEngine::Simulation_Start(Filename);
	return;
}

void DESEngine::SysFct_HALT(const std::string &HaltText)
{
	Halted = true;
}

// Sets the label to current EventPointer.
// If two label names collide, the first is overwritten
void DESEngine::SysFct_LABEL(const std::string &Label)
{
	GVar_EventLabels.VarSet(Label, EventPointer);
	return;
}

// If the label is set, puts EventPointer to Label+1
void DESEngine::SysFct_GOTO(const std::string &Label)
{
	if (GVar_EventLabels.VarGet_Int(Label, -1) != -1)
	{
		EventPointer = GVar_EventLabels.VarGet_uInt(Label) + 1;
	}
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
				Param = WordBlock;
				break;
			default:
				// If it doesn't have a pre-param-identifier treat as string
				Param = WordBlock;
				break;
			}
		}

		EvtParams.push_back(Param);
		return;
	}


	// If we reach this point of code that's because:
		// WordBlock.length < 2
		// OR WordBlock.at(1) != '%'; so it doesn't return from function
		// OR It isn't a variable; so it doesn't return from function
	// So we treat it as string:
	Param = WordBlock;
	EvtParams.push_back(Param);
	return;
}
