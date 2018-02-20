// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

// TODO: make this an abstract function

#ifndef H_USEREVENTS
#define H_USEREVENTS


#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <typeinfo>
#include <boost/any.hpp>
#include "GlobalVariables.h"


class UserEvents
{
	
public:
	
	GlobalVariables UserVariables;

	// Class constructor / destructor
	// TODO: Make this have an DESEngine Owner for better event interface
	UserEvents();
	~UserEvents();

	struct EventWithParams { std::string Name; std::vector<boost::any> Params; };

	// Lets an outside class (DESEngine) configure which event to run before calling UserEvents::Choose()
	EventWithParams Event;

	// Select which function(parameters) to call based on the EventWithParams Event (above)
	int UserEvents::Choose();

protected:
	void UserEvents::UserFunctionPointerMap_AddFunction(std::string Alias,
		std::function<void(UserEvents::*)(const std::vector<boost::any>&)> FunctionPointer);

	bool const UserEvents::IsParamVariable(const boost::any &Parameter);

	virtual void UserEvents::BuildUFPAliasMap() = 0;

	std::string UserEvents::Boost2String(const boost::any & Parameter);

private:

	// Here we have an unordered map that assigns User Function (pointer) to each Key (string or Alias\ or Event Name)
	std::unordered_map<std::string, std::function<void(UserEvents::*)(const std::vector<boost::any>&)>> UserFunctionPointerAliasMap;

};

#endif //H_USEREVENTS