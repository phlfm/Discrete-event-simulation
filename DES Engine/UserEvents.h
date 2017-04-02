// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

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
	void Add(const void *Parameters, void *ReturnValue);
};

