#include "GlobalVariables.h"
#include <typeinfo>



GlobalVariables::GlobalVariables()
{

}


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
	VarMap.insert_or_assign(Key, Value);//(std::pair<std::string, boost::any>(Key, Value));
	return;
}

boost::any const GlobalVariables::VarGet(const std::string Key, const boost::any DefaultNotFound)
{
	try
	{
		return VarMap.at(Key);
	}
	catch (std::out_of_range const &e)
	{
		return DefaultNotFound;
	}
}

// DANGEROUS - I don't know what happens when you edit the contents of this pointer that is a boost::any
void* const GlobalVariables::VarGet_ptr(const std::string Key)
{
	try
	{
		return &VarMap.at(Key);
	}
	catch (std::out_of_range const &e)
	{
		return nullptr;
	}
}

std::string const GlobalVariables::VarGet_Type(const std::string Key)
{
	if (VarMap.at(Key).empty()) { return "EMPTY"; }

	// TODO: make a better return for string instead of:
	//		 class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
	return VarMap.at(Key).type().name();
}

