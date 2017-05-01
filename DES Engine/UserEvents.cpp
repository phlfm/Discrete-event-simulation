// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"

// Class Constructor
UserEvents::UserEvents(GlobalVariables &GV)
{
	GlobalVar = &GV;
	//EventList.clear;
	BuildUFPAliasMap();
}

// Class Destructor
UserEvents::~UserEvents()
{
	
}

// Select which function(parameters) to call depending on event alias and returns ReturnValue
// Returns 0 = UserFunction, 1 = SystemFunction, -1 if no function found
int UserEvents::Choose(const std::string Alias, const void *Parameters, void *ReturnValue)
{
	// TODO: Treat exception if alias doesnt exist
	(this->*UFPAliasMap.at(Alias))(Parameters, ReturnValue);
	
	//TODO: What do if no alias is found?
	return 0;
}

/**/
// Returns an std::vector with the event list. EventList = {"add", {2, 3, *C}}
void UserEvents::GetEventList(const std::string &Filename)
{
	// Get File lines and line count
	TextParser TP(Filename);
	unsigned int fLineCount = TP.GetLineCount();

	// Variables used in the loop
	std::string				 Line = "";
	std::vector<std::string> WordBlocks;
	std::string				 EventName;
	std::vector<boost::any>  EvtParams;

	EventList.clear();

	// Loop Lines of FLIN
	for (unsigned int i = 1; i <= fLineCount; i++)
	{
		Line = TP.GetLine(i);
		TP.GetWordBlocks(WordBlocks, Line, true); // Because of how ExtractEventParameter, Append%s should be optional

		EvtParams.clear();
		// Get event parameters by looping WordBlocks from 1 to size-1
		for (unsigned j = 1; j < WordBlocks.size(); j++)
		{
			// Extracts the next Event Parameter appropriately
			ExtractEventParameter(WordBlocks.at(j), EvtParams);
		}

		// Get event name
		if (WordBlocks.size() > 0)
		{
			EventName = WordBlocks.at(0);
			EventList.push_back({ EventName, EvtParams });
		}

	}

	//delete &TP;
	return;
}

// Extracts the corresponding Event Parameters
// Warning: "Ruins" the contents of WordBlock
void UserEvents::ExtractEventParameter(std::string &WordBlock, std::vector<boost::any> &EvtParams)
{
	// Pre-Parameter Identifiers:
		// s%, i%, l%, f%, d% --> %u is not working
		// string, int, long, float, double --> unsigned long not working
		// s% is optional because it's the default action

	boost::any Param;

	if (WordBlock.length() > 2)
	{
		// If it starts with $ it's a GlobalVariable, get GlobalVariable PTR
		if (WordBlock.at(0) == '$')
		{
			WordBlock.erase(0, 1); // Erases the $
			Param = GlobalVar->VarGet_ptr(WordBlock);
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
				//case 'u':
				//	WordBlock.erase(0, 2); // Erases the identifier  u%
				//	Param = std::stoul(WordBlock);
				//	break;
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

// Builds the UserFunctionPointerAliasMap
void UserEvents::BuildUFPAliasMap()
{
	// If UserFunctions use the same alias as system functions, they will be overwritten.
	// For this reason don't start user function aliases with @

	// Add user functions below:
	UFPAliasMap.insert({ "ADD", &UserEvents::Add });

	// System Functions below:
	//UFPAliasMap.insert_or_assign("Add", &UserEvents::Add);
}

#pragma region User Functions

// User must modify void UserEvents::BuildUFPAliasMap()
void UserEvents::Add(const void *Parameters, void *ReturnValue)
{
	int *A = (int*)Parameters;
	int *B = A;
	B++;

	int *C = (int*)ReturnValue;
	*C = *A + *B;

	//memcpy(ReturnValue, &C, sizeof(int));
	return;
}

#pragma endregion Implementation of User Functions

#pragma region System Functions

//void UserEvents::Add(const void *Parameters, void *ReturnValue)
//{
//	int *A = (int*)Parameters;
//	int *B = A;
//	B++;
//
//	int *C = (int*)ReturnValue;
//	*C = *A + *B;
//
//	//memcpy(ReturnValue, &C, sizeof(int));
//	return;
//}

#pragma endregion Implementation of System Functions


/* Text File Symbols

@	System Commands
//	Comment
$	Variable
"	Delimits strings (multi lines are not supported)
/"
i%, l%, u%, f%, d%, (optional) s%	determines the parameter type
If parameter type is not determined, treat as string
Each line should be:
COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
*/
/**/