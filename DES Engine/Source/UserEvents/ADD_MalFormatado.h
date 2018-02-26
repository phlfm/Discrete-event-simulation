// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_ADDMALFORMATADO
#define H_ADDMALFORMATADO

#include <iostream>
#include <memory>
#include "../Event.h"
#include "../SystemManager.h"

using namespace DESE;

namespace ADDMALFORMATADO
{
	bool const IsParamVariable(const boost::any & Parameter)
	{
		std::string ParamStr = Boost2String(Parameter);

		if (ParamStr == "") { return false; }
		// If we reach here, that means Parameter was cast into string
		if (ParamStr.at(0) == '$') { return true; }
		return false;
	}

	class UserEvent_ADD : public Event {
	public:
		UserEvent_ADD(SystemManager* SysMan) : Event(SysMan) {};
		virtual void Run(const vector<boost::any> &Parameters) {
			// Get A
			int A;
			if (IsParamVariable(Parameters.at(0)))
			{
				A = SysMan->UserVariables.VarGet_casted<int>(Boost2String(Parameters.at(0)));
			}
			else
			{
				A = boost::any_cast<int>(Parameters.at(0));
			}
			// Get B
			int B;
			if (IsParamVariable(Parameters.at(1)))
			{
				B = SysMan->UserVariables.VarGet_casted<int>(Boost2String(Parameters.at(1)));
			}
			else
			{
				B = boost::any_cast<int>(Parameters.at(1));
			}
			// Store A+B
			SysMan->UserVariables.VarSet(Boost2String(Parameters.at(2)), A + B);
			std::cout << Boost2String(Parameters.at(2)) << " = " << A << " + " << B << " = " << A + B << std::endl;
			if (A + B > 5) { SysMan->UserVariables.VarSet("$UserHalt", 1); }
			return;
		};
	}; ///ADD

	class UserEvent_PRINT : public Event {
	public:
		UserEvent_PRINT(SystemManager* SysMan) : Event(SysMan) {};
		virtual void Run(const vector<boost::any> &Parameters) {
			std::cout << "Print called...\n";
			return;
		};
	}; ///PRINT

	struct UserEvent_Collection {
		UserEvent_Collection(SystemManager *SysMan) : Evt_Add(SysMan), Evt_Print(SysMan) {};
		void RegisterEvents(SystemManager *SysMan)
		{
			SysMan->Event_Catalog.RegisterEvent("ADD", &Evt_Add);
			SysMan->Event_Catalog.RegisterEvent("PRINT", &Evt_Print);

		}
		UserEvent_ADD Evt_Add;
		UserEvent_PRINT Evt_Print;
	}; /// sturct UserEvent__Collection

} /// namespace ADDMALFORMATADO
#endif // H_ADDMALFORMATADO