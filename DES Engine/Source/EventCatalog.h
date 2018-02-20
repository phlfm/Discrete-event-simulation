// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_EVENTCATALOG
#define H_EVENTCATALOG

#include <string>
#include <unordered_map>

using std::unordered_map; using std::string;

namespace DESE {

	class Event;

	class EventCatalog
	{

	public:
		// Registers a new event into the internal Event Catalog. Users must not register events starting with @.
		void RegisterEvent(string EventName, Event *Event);

		// Given an event name it returns the pointer stored to that event.
		// Should the event be reinstantiated, the stored event pointer is updated if necessary.
		Event* getEvent(string EventName);

	protected:
		unordered_map<string, Event*> eventCatalog;

}; // class EventCatalog
} // namespace DESE
#endif //H_EVENTCATALOG