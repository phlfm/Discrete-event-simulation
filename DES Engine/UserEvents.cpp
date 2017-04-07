// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"
#include <iostream>

// Class Constructor
UserEvents::UserEvents()
{
	BuildUFPAliasMap();
}

// Class Destructor
UserEvents::~UserEvents()
{
}

// Select which function(parameters) to call depending on event alias and returns ReturnValue
void UserEvents::Choose(const std::string Alias, const void *Parameters, void *ReturnValue)
{
	for (int i = 0; i < UFPAliasMap.size(); i++)
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
			return;
		}
	}

	//TODO: What do if no alias is found?
}

#pragma region UFPMap Definitions

// Constructs the struct FunctionPointerAlias { std::string FAlias; void(*FPointer)(const void*, void*); };
UserEvents::FunctionPointerAlias UserEvents::MakeFPAlias(std::string FAlias, void(UserEvents::*FPointer)(const void *, void *))
{
	FunctionPointerAlias Return = { FAlias, FPointer };
	return Return;
}

// Builds the UserFunctionPointerAliasMap
void UserEvents::BuildUFPAliasMap()
{
	UFPAliasMap.push_back(MakeFPAlias("Add", &UserEvents::Add));
	UFPAliasMap.shrink_to_fit();
}
#pragma endregion



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

