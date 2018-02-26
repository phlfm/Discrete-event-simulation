// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018

#ifndef H_MAIN
#define H_MAIN


#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include "DESEngine.h"
#include "UserEvents/ADD_MalFormatado.h"

int main();

#pragma region Test Functions

// Includes for Test Funcions
#include <iostream>
#include <string>
//#include "boost/any.hpp"
//#include <typeinfo>

//void TEST_UserEvents_ADD(UserEvents &UE);

void TEST_BoostAnyPTR();

void TEST_GlobalVariableSetGetType(DESE::GlobalVariables &GV);

// Makes TextParser ready for action
void TEST_TextParser(DESE::TextParser &TP);
void TEST_TextParser_PrintFile(DESE::TextParser &TP);
void TEST_TextParser_WordBlock(DESE::TextParser &TP);


#pragma endregion

#endif //H_MAIN