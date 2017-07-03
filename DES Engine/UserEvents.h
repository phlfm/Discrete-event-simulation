// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#ifndef USEREVENTS
#define USEREVENTS


#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <boost/any.hpp>
#include "GlobalVariables.h"

class UserEvents
{
	
public:
	
	GlobalVariables UserVariables;

	// Class constructor / destructor
	UserEvents();
	~UserEvents();

	struct EventWithParams { std::string Name; std::vector<boost::any> Params; };

	// Lets an outside class (DESEngine) configure which event to run before calling UserEvents::Choose()
	EventWithParams Event;

	// Select which function(parameters) to call based on the EventWithParams Event (above)
	int UserEvents::Choose();

	
private:

	// Here we have an unordered map that assigns User Function (pointer) to each Key (string or Alias or Event Name)
	std::unordered_map<std::string, void(UserEvents::*)(const std::vector<boost::any>&)> UserFunctionPointerAliasMap;

	bool const UserEvents::IsParamVariable(const boost::any &Parameter);
	

	void UserEvents::BuildUFPAliasMap();

	std::string UserEvents::Boost2String(const boost::any & Parameter);
	
// User Functions / Events
	void UserEvents::Add(const std::vector<boost::any> &Parameters);

};

#endif