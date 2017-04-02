// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"


// Class Constructor
UserEvents::UserEvents()
{
}

// Class Destructor
UserEvents::~UserEvents()
{
}

// Select which function(parameters) to call depending on event alias and returns ReturnValue
void UserEvents::Choose(const std::string Alias, const void *Parameters, void *ReturnValue)
{
	// TODO: ChooseTable[string Alias, function pointer Function] then given alias (eg "Add"), search for it in the table and call the respective function pointer.
	// TODO: User - Implement Function Choose
	if (Alias == "Example")
	{
		// *ReturnValue = Function(Parameters)
		return;
	}

	if (Alias == "Add") { UserEvents::Add(Parameters, ReturnValue);  return; }

	// If we reach the bottom, no alias was found for that event
	//*ReturnValue = "halt" ??;
}


#pragma region UserFunctions

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

