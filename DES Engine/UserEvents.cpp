// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "UserEvents.h"

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
	std::string ParamStr;

	// Convert Parameter to std::string
	try
	{
		ParamStr = boost::any_cast<std::string>(Parameter);
	}
	catch (const boost::bad_any_cast e)
	{
		try
		{
			ParamStr = (std::string)(boost::any_cast<const char*>(Parameter));
		}
		catch (const boost::bad_any_cast e)
		{
			return false;
		}
	}
	// End Conversion

	// If we reach here, that means Parameter was cast into string
	if (ParamStr.at(0) == '$') { return true; }
	return false;
}

// Builds the UserFunctionPointerAliasMap
void UserEvents::BuildUFPAliasMap()
{
	// If UserFunctions use the same alias as system functions, they will not be called.
	// For this reason don't start user function aliases with @

	// Add user functions below:
	UserFunctionPointerAliasMap.insert({ "ADD", &UserEvents::Add });

}

#pragma region User Functions

// User must modify void UserEvents::BuildUFPAliasMap()
void UserEvents::Add(const std::vector<boost::any> &Parameters)
{
	int A = boost::any_cast<int>(Parameters.at(0));
	int B = boost::any_cast<int>(Parameters.at(1));

	UserVariables.VarSet("add", A + B);
	return;
}

#pragma endregion Implementation of User Functions

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