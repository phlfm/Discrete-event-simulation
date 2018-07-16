// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018
// C++ Core "Standard" by Bjarne Stroustrup: https://goo.gl/4bziNu


#ifndef H_SYSMAN
#define H_SYSMAN
#pragma once

#include "boost/any.hpp"
#include <string>
#include <iostream>
#include <windows.h> // For colored console

#include "EventList.h"
#include "EventCatalog.h"
#include "GlobalVariables.h"


using std::string; using std::vector; using boost::any;

namespace DESE {
	struct Engine_Settings {
		bool Print_SystemCommands = false; // Print system commands to console
		bool GoTo_Print = false; // What?
		bool GoTo_HaltOnFail = true;
	}; /// Engine_Settings

	enum Engine_Status { NotInstantiated, Constructed, Simulation_Running, Simulation_Halted_byEvent, Simulation_Halted_noMoreEvents, Simulation_Failed };

	struct SystemManager {
		EventList Event_List;
		EventCatalog Event_Catalog;
		GlobalVariables UserVariables;
		Engine_Settings Settings;
		Engine_Status Status = NotInstantiated;

		bool SystemManager::ShouldStop() {
			if (this->Event_List.isFinished()) { return true; }
			if (this->Status == Simulation_Halted_byEvent) { return true; }
			if (this->Status == Simulation_Halted_noMoreEvents) { return true; }
			if (this->Status == Simulation_Failed) { return true; }

			return false;
		}
	}; ///SystemManager

	namespace { //anonymous namespace start
		/* These functions were causing linking errors "function already defined in FILE"
		A possible solution would be declaring them static, but anonymous namespace is a superior solution
		https://stackoverflow.com/questions/154469/unnamed-anonymous-namespaces-vs-static-functions
		*/
		std::string Boost2String(const boost::any & Parameter)
		{
			std::string ParamStr;

			// Convert Parameter to std::string
			try
			{
				ParamStr = (std::string)(boost::any_cast<const char*>(Parameter));
			}
			catch (const boost::bad_any_cast e)
			{
				try
				{
					ParamStr = boost::any_cast<std::string>(Parameter);
				}
				catch (const boost::bad_any_cast e)
				{
					return "";
				}
			}

			return ParamStr;
		}

		//template <typename T>
		void PrintSysMsg(std::string Message, const SystemManager *SysMan, int OutputColor = 4, int DefaultColor = 7)
		{
			if (SysMan->Settings.Print_SystemCommands)
			{
				// Set console color
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, OutputColor);

				std::cout << Message;

				// Reset to default console color
				SetConsoleTextAttribute(hConsole, DefaultColor);

			} // close if

			return;
			// Color codes:
			// DARK	1		2		3		4		5		6		7		 8
			//		Blue	Green	Cyan	Red		Purple	Gold	Whiteish Gray
			// LIGHT	9		10		11		12		13		14		15	
			//			Blue	Green	Cyan	Red		Purple	Yellow	White
			// 16 to ... = Same colors but with blue background
			// 16 = 10 in hexa = darkblue background + black font)
		} ///void PrintSysMsg
	}//anonymous namespace end
} /// namespace DESE
#endif /// H_SYSMAN
