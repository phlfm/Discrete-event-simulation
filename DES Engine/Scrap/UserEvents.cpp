// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#include "UserEvents.h"

// Class Constructor
UserEvents::UserEvents()
{
	UserVariables = GlobalVariables();
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
		std::function<void(UserEvents::*)(const std::vector<boost::any>&)> FctPtr =
			UserFunctionPointerAliasMap.at(Event.Name);
		//&FctPtr();
		//(UserFunctionPointerAliasMap.at(Event.Name))(Event.Params);
		//(this->*UserFunctionPointerAliasMap.at(Event.Name))(Event.Params);
		return 0;
	}
	catch (const std::out_of_range e)
	{
		throw std::exception::exception("Unknown User Event");
		return -1;
	}
}

void UserEvents::UserFunctionPointerMap_AddFunction(std::string Alias, 
	std::function<void(UserEvents::*)(const std::vector<boost::any>&)> FunctionPointer)
{
	UserFunctionPointerAliasMap.insert({Alias, FunctionPointer});
	return;
}

// Returns true if boost::any Parameter is a string and starts with '$'
bool const UserEvents::IsParamVariable(const boost::any & Parameter)
{
	std::string ParamStr = Boost2String(Parameter);
	
	if (ParamStr == "") { return false; }
	// If we reach here, that means Parameter was cast into string
	if (ParamStr.at(0) == '$') { return true; }
	return false;
}

// Safely casts a boost::any into std::string
std::string UserEvents::Boost2String(const boost::any & Parameter)
{
	std::string ParamStr;

	// Convert Parameter to std::string
	try
	{
		// TODO: Make this more C++ ish
		// ParamStr = std::string((boost::any_cast<const char*>(Parameter)));
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
