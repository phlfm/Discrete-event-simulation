// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/any.hpp>
#include <unordered_map>
#include "TextParser.h"
#include "GlobalVariables.h"



class UserEvents
{
	
public:
	
	// Class constructor / destructor
	UserEvents(GlobalVariables &GV);
	~UserEvents();

	struct EventWithParams { std::string EventName; std::vector<boost::any> EventParams; };
	std::vector<EventWithParams> EventList;

	GlobalVariables *GlobalVar;

	// Select which function(parameters) to call depending on event alias and returns ReturnValue
	int Choose(const std::string Alias, const void *Parameters, void *ReturnValue);

	void UserEvents::GetEventList(const std::string &Filename);

private:

	void UserEvents::ExtractEventParameter(std::string &WordBlock, std::vector<boost::any> &EvtParams);

	// Here we have an unordered map that assigns User Function (pointer) to each Key (string / Alias / Event Name)
	std::unordered_map<std::string, void(UserEvents::*)(const void*, void*)> UFPAliasMap;

	void BuildUFPAliasMap();

	void Add(const void *Parameters, void *ReturnValue);
};

