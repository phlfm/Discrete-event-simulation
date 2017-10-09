// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2017
#ifndef H_DESENGINE
#define H_DESENGINE

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "boost/any.hpp"
#include "GlobalVariables.h"
#include "TextParser.h"
#include "UserEvents.h"
#include <windows.h> // For colored console

class GlobalVariables;
class TextParser;
class UserEvents;

class DESEngine
{
public:
// System Classes
	GlobalVariables GVar_EventLabels;
	UserEvents UsrEvt;

// System Variables
	struct EventWithParams { std::string Name; std::vector<boost::any> Params; };
	std::vector<EventWithParams> EventList;
	unsigned int EventPointer = 0;
	unsigned int EntryPoint = 0; // Useful for iterative calculations
	bool PurgeUserVariablesOnStart = true; // Useful for iterative calculations
	bool PrintSystemCommands = true; // Should system commands print to console?
	bool PrintHaltFailed = false;
	bool PrintGoto = false;
	bool Halted = false;
	
// Class methods
	DESEngine();
	~DESEngine();

	void DESEngine::EventList_Load(const std::string &Filename);

	// Starts the Simulation on the Currently loaded EventList
	bool DESEngine::Simulation_Start();

	// Loads a NEW EventList and calls Simulation_Start()
	bool DESEngine::Simulation_Start(const std::string &Filename);
	void DESEngine::Simulation_Restart(const std::string &Filename);
	void DESEngine::Event_Select(const EventWithParams &Event);

	void DESEngine::SysFct_HALT(const std::string &HaltTestVariable); // Tests user variable HaltTestVariable != 0
	void DESEngine::SysFct_LABEL(const std::string &Label); // creates label with string as name
	void DESEngine::SysFct_GOTO(const std::string &Label);  // goes to label (prints and does nothing if label doesnt exist)


private:
	TextParser TxtPar;

	void Simulation_Loop();

	std::unordered_map<std::string, void(DESEngine::*)(const std::string&)> SystemFunctionPointerMap;
	void DESEngine::BuildSystemEventsAlias();

	void DESEngine::ExtractEventParameter(std::string &WordBlock, std::vector<boost::any> &EvtParams);

	std::string DESEngine::Boost2String(const boost::any & Parameter);

	void DESEngine::PrintSYS(const char * Message, int OutputColor = 4, int DefaultColor = 7);
	void DESEngine::PrintSYS(std::string Message, int OutputColor = 4, int DefaultColor = 7);
};

#endif // H_DESENGINE
