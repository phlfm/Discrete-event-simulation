// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018
#include "EventCatalog.h"
#include "Event.h"

using std::unordered_map; using std::string;

		// Registers a new event into the internal Event Catalog. Users must not register events starting with @.
		void DESE::EventCatalog::RegisterEvent(string EventName, DESE::Event *Event)
			{ eventCatalog.insert({ EventName, Event }); }

		// Given an event name it returns the pointer stored to that event.
		// Should the event be reinstantiated, the stored event pointer is updated if necessary.
		DESE::Event* DESE::EventCatalog::getEvent(string EventName) {
			DESE::Event *thisEvent = eventCatalog.at(EventName);
			// Reinstantiate if necessary
			if (thisEvent->shouldReinstantiate())
			{
				thisEvent->Reinstantiate(thisEvent); // Updates thisEvent with a new pointer if necessary
				eventCatalog.at(EventName) = thisEvent; //Update catalog with new event pointer
			}

			return thisEvent;
		} //Event* getEvent
