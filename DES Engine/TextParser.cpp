// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "TextParser.h"


TextParser::TextParser(const char *Filename)
{
	FileLoadLines(Filename);
}

TextParser::TextParser()
{
}

TextParser::~TextParser()
{
}

unsigned int TextParser::FileLineCount()
{
	return flin.size();
}

std::string TextParser::FileGetLine(const unsigned int LineNumber)
{
	return flin.at(LineNumber);
}


// Returns an std::vector with the event list. EventList = {"add", {2, 3, *C}}
void TextParser::GetEventList(std::vector<std::string, std::vector<boost::any>> *EventList)
{
// FLIN should be: COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
	// Loop Lines of FLIN
		// Break line into spaces

		// Get and Store COMMAND block

		// Loop Parameters
			// If(Param == Comment)
				// IGNORE Rest of Param; next line
			// NOT(Comment)
				// If(Param == pre-defined) 	(c%, i%, ui%, l%, ul%, f%, d%)
					// Store Parameter
				// NOT(Pre-defined)
					// If(Param == String Param ("))
						// Loop until ending string found (")
						// Store string Parameter
						// Set Param iterator to position after ending string (")
					// NOT(String)
						// Store char* Parameter (same as c%)
	return;
}
/* Text File Symbols

@	System Commands
//	Comment
$	Variable
"	Delimits strings (multi lines are not supported)
/"	
c%, i%, ui%, l%, ul%, f%, d%	determines the parameter type
If parameter type is not determined, treat as char*
Each line should be:
COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
*/


int TextParser::FileLoadLines(const char *Filename)
{
	std::ifstream file(Filename, std::ifstream::in);
	std::string str;

	// Checks for "fail" and "bad"
	if (!file) { return 1; }

	flin.clear();

	while (std::getline(file, str))
	{
		flin.push_back(str);
	}

	file.close();

	flin.shrink_to_fit();

	return 0;
}