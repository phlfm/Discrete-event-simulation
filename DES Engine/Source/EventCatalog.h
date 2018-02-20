// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_EVENTCATALOG
#define H_EVENTCATALOG

#include <string>
#include <unordered_map>
#include "Event.h"

using std::unordered_map; using std::string;

namespace DESE {

	class EventCatalog
	{

	public:
		// Registers a new event into the internal Event Catalog. Users must not register events starting with @.
		void RegisterEvent(string EventName, class Event *Event)
			{ eventCatalog.insert({ EventName, Event }); }

		// Given an event name it returns the pointer stored to that event.
		// Should the event be reinstantiated, the stored event pointer is updated if necessary.
		class Event* getEvent(string EventName) {
			class Event *thisEvent = eventCatalog.at(EventName);
			// Reinstantiate if necessary
			if (thisEvent->shouldReinstantiate())
			{
				thisEvent->Reinstantiate(thisEvent); // Updates thisEvent with a new pointer if necessary
				eventCatalog.at(EventName) = thisEvent; //Update catalog with new event pointer
			}

			return thisEvent;
		} //Event* getEvent

	protected:
		unordered_map<string, class Event*> eventCatalog;

}; // class EventCatalog
} // namespace DESE
#endif //H_EVENTCATALOG