// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_EVENT
#define H_EVENT

#include <string>
#include <vector>
#include "SystemManager.h"

using std::string; using std::vector;

namespace DESE {

	class Event
	{

	public:
		Event(SystemManager *SystemManager = nullptr, bool shouldReinstantiate = false)
			: SysMan(SystemManager), should_Reinstantiate(shouldReinstantiate) {}

		virtual ~Event() {};

		virtual void Run(const vector<boost::any> &Parameters) = 0;

		// This function allows for a soft reinstantiation or a hard one
		// (hard instantiation requires user to change CurrentEventHandler to a "new Event*" and "delete this;")
		virtual void Reinstantiate(Event* CurrentEventHandler) { return; }

		bool shouldReinstantiate() { return should_Reinstantiate; }
		void shouldReinstantiate(bool shouldReinstantiate) { should_Reinstantiate = shouldReinstantiate; return; }

	protected:

		bool should_Reinstantiate = false;
		SystemManager *SysMan = nullptr;

}; // class Event
} // namespace DESE
#endif // H_EVENT