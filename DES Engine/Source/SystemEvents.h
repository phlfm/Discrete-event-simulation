// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_SYSEVENTS
#define H_SYSEVENTS

#include "Event.h"
#include "SystemManager.h"


namespace DESE {

	struct SysEvent_Collection {
		void RegisterEvents(SystemManager *SysMan)
		{
			SysMan->Event_Catalog.RegisterEvent("@HALT", &Evt_Halt);
			SysMan->Event_Catalog.RegisterEvent("@GOTO", &Evt_Goto);

			SysMan->Event_Catalog.RegisterEvent("LABEL", &Evt_Label);
			SysMan->Event_Catalog.RegisterEvent("@@", &Evt_Label);
		}
		class SysEvent_HALT Evt_Halt;
		class SysEvent_GOTO Evt_Goto;
		class SysEvent_LABEL Evt_Label;
	};


	class SysEvent_HALT : public Event {
	public:
		// If no parameter is found, halts execution. If at least one parameter is found, it is treated as
		// a user variable and if that user variable is diferent from zero, simulation is halted.
		virtual void Run(const vector<boost::any> &Parameters) {
			// If no parameter is found, halt simulation and return from event call.
			if (Parameters.size() == 0) { SysMan->Status = Simulation_Halted_byEvent; return; }

			// if at least one parameter is found, loop looking for a Halt Test Variable,
			// if this variable evaluates to anything other than zero, simulation is halted.
			std::string HaltTestVariable = "";
			for (int i = 0; i < Parameters.size(); ++i) {
				HaltTestVariable = Boost2String(Parameters.at(i));
				if (SysMan->UserVariables.VarExists(HaltTestVariable))
				{
					if (SysMan->UserVariables.VarGet_casted<int>(HaltTestVariable) != 0)
					{
						// HaltTestVariable != 0 --> HALT
						PrintSysMsg("SysEvent_HALT: Halt test passed, halting engine...\n", SysMan);
						SysMan->Status = Simulation_Halted_byEvent;
						return;
					}
				} else // HaltTestVariable doesnt exist
				{
					PrintSysMsg("SysEvent_HALT: Halt test variable not found (" + HaltTestVariable + "\n", SysMan);
				}
			} /// for loop
			// No Suitable halt parameter found - do nothing
			PrintSysMsg("SysEvent_HALT: No suitable halt condition found, resuming simulation.\n", SysMan);
			return;
		} /// Halt::RUN
	}; ///HALT

	class SysEvent_LABEL : public Event {
	public:
		virtual void Run(const vector<boost::any> &Parameters) {}; //do nothing
	}; ///LABEL

	class SysEvent_GOTO : public Event {
	public:
		// Goes to the first label in EventList that matches at least one parameter.
		virtual void Run(const vector<boost::any> &Parameters)
		{
			// If no parameter is found, do nothing
			if (Parameters.size() == 0) { return; }

			// if at least one parameter is found, loop looking for a valid label location
			std::string TestLabel = "";
			unsigned int LabelIndex = 0;
			for (int i = 0; i < Parameters.size(); ++i) {
				TestLabel = Boost2String(Parameters.at(i));
				LabelIndex = SysMan->Event_List.findLabel(TestLabel); // returns label index +1. Zero if no label found.
				if (LabelIndex != 0)
				{
					if (SysMan->Settings.GoTo_Print) PrintSysMsg("GOTO " + TestLabel + " (Event number: " + std::to_string(LabelIndex) + ")\n", SysMan);
					SysMan->Event_List.eventIndex = LabelIndex; return;
				}
			} /// label for loop
			if (SysMan->Settings.GoTo_HaltOnFail) { PrintSysMsg("GOTO FAILED " + TestLabel + "\nSimulation Halting\n", SysMan); SysMan->Status = Simulation_Failed; }
		} /// goto run
	}; ///GOTO
} // namespace DESE
#endif // H_SYSEVENTS