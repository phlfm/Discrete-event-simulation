// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include "boost/any.hpp"
#include "GlobalVariables.h"
#include "UserEvents.h"
#include "TextParser.h"

int main();

#pragma region Test Functions

// Includes for Test Funcions
#include <iostream>
#include <string>

void TEST_UserFunctionADD(UserEvents &UsrEvt);

void TEST_GlobalVariableSetGetType(GlobalVariables &GV);

void TEST_TextParser(TextParser &TP);

#pragma endregion
