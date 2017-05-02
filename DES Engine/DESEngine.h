// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017
#ifndef DESENGING
#define DESENGINE

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "boost/any.hpp"
#include "GlobalVariables.h"
#include "TextParser.h"
#include "UserEvents.h"

class GlobalVariables;
class TextParser;
class UserEvents;

class DESEngine
{
public:
// System Classes
	GlobalVariables GVar_User = GlobalVariables();
	GlobalVariables GVar_EventLabels = GlobalVariables();
	//UserEvents UsrEvt = UserEvents(*this);

// System Variables
	struct EventWithParams { std::string Name; std::vector<boost::any> Params; };
	std::vector<EventWithParams> EventList;
	unsigned int EventPointer = 0;
	unsigned int EntryPoint = 0; // Useful for iterative calculations
	bool PurgeUserVariablesOnStart = true; // Useful for iterative calculations
	bool Halted = false;

	DESEngine();
	~DESEngine();

	void DESEngine::EventList_Load(const std::string &Filename);
	bool DESEngine::Simulation_Start(const std::string &Filename);
	void DESEngine::Simulation_Restart(const std::string &Filename);
	void DESEngine::Event_Select(const EventWithParams &Event);

	void DESEngine::SysFct_HALT(const std::string &HaltText);  // Halts and prints string
	void DESEngine::SysFct_LABEL(const std::string &Label); // creates label with string as name
	void DESEngine::SysFct_GOTO(const std::string &Label);  // goes to label (prints and does nothing if label doesnt exist)


private:
	TextParser TxtPar = TextParser();

	void Simulation_Loop();

	std::unordered_map<std::string, void(DESEngine::*)(const std::string&)> SystemFunctionPointerMap;
	void DESEngine::BuildSystemEventsAlias();

	void DESEngine::ExtractEventParameter(std::string &WordBlock, std::vector<boost::any> &EvtParams);
};

#endif
