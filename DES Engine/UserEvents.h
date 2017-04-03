// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <string>
#include <vector>



class UserEvents
{
	
public:
	struct FunctionPointerAlias { std::string FAlias; void(UserEvents::*FPointer)(const void*, void*); };

	// Here we have a vector that assigns an alias (string) to each User Function (pointer)
	std::vector<FunctionPointerAlias> UFPAliasMap;

	// Constructs the struct FunctionPointerAlias { std::string FAlias; void(*FPointer)(const void*, void*); };
	FunctionPointerAlias MakeFPAlias(std::string FAlias, void(UserEvents::*FPointer)(const void*, void*));

	// Class constructor / destructor
	UserEvents();
	void BuildUFPAliasMap();
	~UserEvents();

	// Select which function(parameters) to call depending on event alias and returns ReturnValue
	void Choose(const std::string Alias, const void *Parameters, void *ReturnValue);


private:

	void Add(const void *Parameters, void *ReturnValue);
};

