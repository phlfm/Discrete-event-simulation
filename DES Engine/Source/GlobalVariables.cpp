// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#include "GlobalVariables.h"

void DESE::GlobalVariables::ClearAllVariables()
{
	VarMap.clear();
	return;
}

void DESE::GlobalVariables::VarSet(const std::string Key, const boost::any Value)
{
	VarMap.insert_or_assign(Key, Value); return;
}

boost::any DESE::GlobalVariables::VarGet(const std::string Key) const
{
	return VarMap.at(Key);
}

void DESE::GlobalVariables::VarDel(const std::string Key)
{
	VarMap.erase(Key);
}

bool DESE::GlobalVariables::VarExists(const std::string Key) const
{
	return (VarMap.find(Key) != VarMap.end()) ? true : false;
}

std::string DESE::GlobalVariables::VarGet_Type(const std::string Key) const
{
	// Make a better return for string instead of: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
	if (VarMap.at(Key).type().name() == typeid(std::string).name()) { return "string"; }

	return VarMap.at(Key).type().name();
}

// boost::any container may store std::string or const char*
std::string DESE::GlobalVariables::VarGet_String(const std::string Key) const
{
	try
		{ return static_cast<std::string>(boost::any_cast<const char*>(VarMap.at(Key))); }
	catch (const boost::bad_any_cast e)
		{ return boost::any_cast<std::string>(VarMap.at(Key));	
	}
}