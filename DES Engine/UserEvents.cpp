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

	int C = *A + *B;
	
	memcpy(ReturnValue, &C, sizeof(int));
	//(int)*ReturnValue = *A;
	return;
}

#pragma endregion Implementation of User Functions

