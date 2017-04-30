// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"

// Class Constructor
UserEvents::UserEvents()
{
	//EventList.clear;
	BuildUFPAliasMap();
}

// Class Destructor
UserEvents::~UserEvents()
{
	UFPAliasMap.~vector();

}

// Select which function(parameters) to call depending on event alias and returns ReturnValue
// Returns i when alias is found, -1 if not found
int UserEvents::Choose(const std::string Alias, const void *Parameters, void *ReturnValue)
{
	for (unsigned int i = 0; i < UFPAliasMap.size(); i++)
	{
		if (Alias == UFPAliasMap[i].FAlias)
		{
			/** Method ONE - Working!!! **/
			void (UserEvents::*FunctionPointer)(const void*, void*) = UFPAliasMap[i].FPointer;
			(this->*FunctionPointer)(Parameters, ReturnValue);
			/**/

			/** Method TWO - Working!!! **
			(this->*UFPAliasMap[0].FPointer)(Parameters, ReturnValue);
			/**/
			return i;
		}
	}

	//TODO: What do if no alias is found?
	return -1;
}

/**
// Returns an std::vector with the event list. EventList = {"add", {2, 3, *C}}
void UserEvents::GetEventList(const std::string &Filename, std::vector<std::string, std::vector<boost::any>> &EventList)
{
	// FLIN should be: COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
	std::string Line = "";

	// Loop Lines of FLIN
	for (unsigned int i = 1; i <= FileLineCount(); i++)
	{
		Line = FileGetLine(i);

		// Break line into spaces
		// Get and Store COMMAND block

		// Loop Parameters
		// If(Param == Comment)
		// IGNORE Rest of Param; next line
		// NOT(Comment)
		// If(Param == pre-defined) 	(c%, i%, ui%, l%, ul%, f%, d%)
		// Store Parameter
		// NOT(Pre-defined)
		// If(Param == String Param ("))
		// Loop until ending string found (")
		// Store string Parameter
		// Set Param iterator to position after ending string (")
		// NOT(String)
		// Store char* Parameter (same as c%)
	}
	return;
}
/* Text File Symbols

@	System Commands
//	Comment
$	Variable
"	Delimits strings (multi lines are not supported)
/"
s%, c%, i%, ui%, l%, ul%, f%, d%	determines the parameter type
If parameter type is not determined, treat as char*
Each line should be:
COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
*/
/**/

// Builds the UserFunctionPointerAliasMap
void UserEvents::BuildUFPAliasMap()
{
	UFPAliasMap.push_back(FunctionPointerAlias {"Add", &UserEvents::Add});
	UFPAliasMap.shrink_to_fit();
}

#pragma region UserFunctions

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

