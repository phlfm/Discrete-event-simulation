#pragma once
#include <string>

class UserEvents
{

public:
	// Class constructor / destructor
	UserEvents();
	~UserEvents();

	// Select which function(parameters) to call depending on event alias and returns ReturnValue
	void Choose(const std::string Alias, const void *Parameters, void *ReturnValue);

private:
	// TODO: User - Implement own functions here
	// Adds OUT *C = A+B;
	void Add(const void *Parameters, void *ReturnValue);
};

