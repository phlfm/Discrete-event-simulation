// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "GlobalVariables.h"



GlobalVariables::GlobalVariables()
{

}

// TODO: GlobalVariables Destructor
GlobalVariables::~GlobalVariables()
{

}

void GlobalVariables::ClearAllVariables()
{
	VarMap.clear();
	return;
}

void GlobalVariables::VarSet(const std::string Key, const boost::any Value)
{
	VarMap.insert_or_assign(Key, Value);
	return;
}

#pragma region Getters

boost::any const	GlobalVariables::VarGet(const std::string Key, const boost::any DefaultNotFound)
{
	try
	{
		return VarMap.at(Key);
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
}

void GlobalVariables::VarDel(const std::string Key)
{
	try
	{
		VarMap.erase(Key);
	}
	catch (const std::out_of_range e)
	{

	}

	return;
}

boost::any* const	GlobalVariables::VarGet_ptr(const std::string Key)
{
	try
	{
		return &VarMap.at(Key);
	}
	catch (const std::out_of_range& e)
	{
		(void)e;
		return nullptr;
	}
}

std::string const	GlobalVariables::VarGet_Type(const std::string Key)
{
	if (VarMap.at(Key).empty()) { return "EMPTY"; }

	// Make a better return for string instead of: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
	if (VarMap.at(Key).type().name() == typeid(std::string).name()) { return "string"; }

	return VarMap.at(Key).type().name();
}

char const			GlobalVariables::VarGet_Char(const std::string Key, char DefaultNotFound, char DefaultBadCast)
{
	try
	{
		return boost::any_cast<char>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}

}

// boost::any container may store std::string or const char*
std::string const	GlobalVariables::VarGet_String(const std::string Key, std::string DefaultNotFound, std::string DefaultBadCast)
{
	try
	{
		return boost::any_cast<std::string>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		try
		{
			return (std::string)(boost::any_cast<const char*>(VarMap.at(Key)));
		}
		catch (const std::out_of_range e)
		{
			return DefaultNotFound;
		}
		catch (const boost::bad_any_cast e)
		{
			return DefaultBadCast;
		}
	}
}

int const			GlobalVariables::VarGet_Int(const std::string Key, int DefaultNotFound, int DefaultBadCast)
{
	try
	{
		return boost::any_cast<int>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}
}

unsigned int const	GlobalVariables::VarGet_uInt(const std::string Key, unsigned int DefaultNotFound, unsigned int DefaultBadCast)
{
	try
	{
		return boost::any_cast<unsigned int>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}
}

long const			GlobalVariables::VarGet_Long(const std::string Key, long DefaultNotFound, long DefaultBadCast)
{
	try
	{
		return boost::any_cast<long>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}
}

unsigned long const GlobalVariables::VarGet_uLong(const std::string Key, unsigned long DefaultNotFound, unsigned long DefaultBadCast)
{
	try
	{
		return boost::any_cast<unsigned long>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}
}

// boost::any stores floats as double, so this function returns float or (float)double
float const			GlobalVariables::VarGet_Float(const std::string Key, float DefaultNotFound, float DefaultBadCast)
{
	try
	{
		return boost::any_cast<float>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		try
		{
			return (float)(boost::any_cast<double>(VarMap.at(Key)));
		}
		catch (const std::out_of_range e)
		{
			return DefaultNotFound;
		}
		catch (const boost::bad_any_cast e)
		{
			return DefaultBadCast;
		}
	}
}

double const		GlobalVariables::VarGet_Double(const std::string Key, double DefaultNotFound, double DefaultBadCast)
{
	try
	{
		return boost::any_cast<double>(VarMap.at(Key));
	}
	catch (const std::out_of_range e)
	{
		return DefaultNotFound;
	}
	catch (const boost::bad_any_cast e)
	{
		return DefaultBadCast;
	}
}

#pragma endregion Global Variable Getters in different formats
