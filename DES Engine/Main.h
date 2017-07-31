// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2017

#ifndef MAIN
#define MAIN


#pragma once
#include "DESEngine.h"
#include "GlobalVariables.h"
#include "TextParser.h"

int main();

#pragma region Test Functions

// Includes for Test Funcions
#include <iostream>
#include <string>
//#include "boost/any.hpp"
//#include <typeinfo>

void TEST_UserEvents_ADD(UserEvents &UE);

void TEST_BoostAnyPTR();

void TEST_GlobalVariableSetGetType(GlobalVariables &GV);

// Makes TextParser ready for action
void TEST_TextParser(TextParser &TP);
void TEST_TextParser_PrintFile(TextParser &TP);
void TEST_TextParser_WordBlock(TextParser &TP);

void TEST_DESEngine();


#pragma endregion

#endif