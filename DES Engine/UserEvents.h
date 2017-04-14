// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <string>
#include <vector>



class UserEvents
{
	
public:
	
	// Class constructor / destructor
	UserEvents();
	~UserEvents();

	// Select which function(parameters) to call depending on event alias and returns ReturnValue
	int Choose(const std::string Alias, const void *Parameters, void *ReturnValue);


private:

	// struct {"Alias", void Function*(void*, void*)}
	struct FunctionPointerAlias { std::string FAlias; void(UserEvents::*FPointer)(const void*, void*); };

	// Here we have a vector that assigns an alias (string) to each User Function (pointer)
	std::vector<FunctionPointerAlias> UFPAliasMap;

	void BuildUFPAliasMap();

	void Add(const void *Parameters, void *ReturnValue);
};

