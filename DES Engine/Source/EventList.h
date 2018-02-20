// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018


/*
Necessidades dessa classe:
	- insert new event no meio da lista.
	- event execution history?

*/
#pragma once
#ifndef H_EVENTLIST
#define H_EVENTLIST

#include <string>
#include <vector>
#include <exception>
#include "boost\any.hpp"

using std::string; using std::vector; using boost::any;

namespace DESE {

	struct EventEntry { string Name; vector<any> Params;};

	struct EventList : public vector<EventEntry>
	{
		// Returns true if end of event list is reached.
		bool isFinished() const { return (eventIndex >= size()); }

		// Returns the next event and increments the internal event index
		EventEntry getNextEvent() { return at(eventIndex++); }

		// Returns the found label event index +1. Returns 0 if not found.
		unsigned int findLabel(const string &Label) {
			for (unsigned int i = 0; i < size(); ++i)
			{
				if (at(i).Name == "LABEL " + Label) return ++i;
				if (at(i).Name == "@@ " + Label) return ++i;
			}

			return 0;
		}

		unsigned int eventIndex = 0;
	}; // struct EventList
} // namespace DESE
#endif //H_EVENTLIST