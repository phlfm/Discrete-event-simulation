// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#ifndef USEREVENTS
#define USEREVENTS


#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <boost/any.hpp>
// #include "DESEngine.h" --> moved to DESEngine.cpp

class DESEngine;

class UserEvents
{
	
public:
	
	// Class constructor / destructor
	UserEvents(DESEngine &Engine);
	~UserEvents();

	// Select which function(parameters) to call
	int UserEvents::Choose(const DESEngine::EventWithParams &Event);

	
private:
	DESEngine Owner;

	// Here we have an unordered map that assigns User Function (pointer) to each Key (string / Alias / Event Name)
	std::unordered_map<std::string, void(UserEvents::*)(const std::vector<boost::any>&)> UserFunctionPointerAliasMap;

	bool const UserEvents::IsParamVariable(const boost::any &Parameter);


	void UserEvents::BuildUFPAliasMap();
	
// User Functions / Events
	void UserEvents::Add(const std::vector<boost::any> &Parameters);

};

#endif