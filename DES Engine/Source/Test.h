// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#pragma once
#ifndef H_TESTE
#define H_TESTE

// STD and Boost Includes
	#include <iostream>
	#include <string>
	//#include "boost/any.hpp"
	//#include <typeinfo>

// DESEngine Includes
	#include "GlobalVariables.h"
	#include "TextParser.h"
	#include "UserEvents.h"
	#include "DESEngine.h"


class Test
{
public:
	Test();
	~Test();

	void UserEvents_ADD(UserEvents &UE);

	void BoostAnyPTR();

	void GlobalVariableSetGetType(GlobalVariables &GV);

	// Makes TextParser ready for action
	void TextParserInit(TextParser &TP);
	void TextParser_PrintFile(TextParser &TP);
	void TextParser_WordBlock(TextParser &TP);

	void DESEnginee();


private:
	GlobalVariables *GlobVar;
	TextParser *TxtPar;
	DESEngine *DESEng;

};


#endif
