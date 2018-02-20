// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018
#pragma once
#ifndef H_DESENGINE
#define H_DESENGINE
// STD includes:
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "boost/any.hpp" //C++17: Update to std::any
// My Includes:
#include "TextParser.h"
#include "Event.h"
#include "SystemManager.h"
#include "SystemEvents.h"


using std::string; using std::vector; using boost::any;

namespace DESE {

	class DESEngine
	{
	public:
		// User MUST populate at least EventCatalog, the rest is optional.
		DESEngine(SystemManager SystemManager);
		~DESEngine();

		void DESEngine::EventList_Load(const std::string &Filename);

		// Loads a NEW EventList and calls Simulation_Start()
		void DESEngine::Simulation_Start(const std::string &Filename);
		void DESEngine::Simulation_Start();
		
	protected:
		// SysMan stores event list, catalog, user variables, engine settings, ...
		SystemManager SysMan;
		
		std::unordered_map<std::string, Event*> SystemEvents;

		void Simulation_Loop();
		void Simulation_End();
		void Print_AllSettings();
		void DESEngine::ExtractEventParameter(std::string &WordBlock, std::vector<boost::any> &EvtParams);
		
		
	}; /// class DESEngine

} /// namespace DESE
#endif /// H_DESENGINE
