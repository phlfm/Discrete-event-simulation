// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "boost/any.hpp"
#include "GlobalVariables.h"
#include "TextParser.h"
#include "UserEvents.h"


class DESEngine
{
public:
// System Classes
	GlobalVariables GVar_User;
	GlobalVariables GVar_EventLabels;
	TextParser TxtPar;
	UserEvents UsrEvt = UserEvents(*this);

// System Variables
	struct EventWithParams { std::string EventName; std::vector<boost::any> EventParams; };
	std::vector<EventWithParams> EventList;
	unsigned int EventPointer = 0;

	DESEngine();
	~DESEngine();

	void DESEngine::EventList_Load(const std::string &Filename);
	void DESEngine::Simulation_Start();
	void DESEngine::Event_Select(const EventWithParams &Event);

	void DESEngine::SysFct_HALT(const std::string);  // Halts and prints string
	void DESEngine::SysFct_LABEL(const std::string); // creates label with string as name
	void DESEngine::SysFct_GOTO(const std::string);  // goes to label (prints and does nothing if label doesnt exist)


private:
	std::unordered_map<std::string, void(DESEngine::*)(const std::string)> SystemFunctionPointerMap;
	void DESEngine::BuildSystemEventsAlias();







};

