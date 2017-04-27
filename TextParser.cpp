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

// LineNumber goes from [1, FileLineCount]
std::string TextParser::FileGetLine(const unsigned int LineNumber)
{
	return flin.at(LineNumber - 1);
}


// Returns an std::vector with the event list. EventList = {"add", {2, 3, *C}}
void TextParser::GetEventList(std::vector<std::string, std::vector<boost::any>> *EventList)
{
// FLIN should be: COMMAND i%PARAM1 f%PARAM2 "Param 3" PARAM4 ...
	std::string Line = "";

	// Loop Lines of FLIN
	for (unsigned int i = 1; i <= FileLineCount(); i++)
	{
		Line = FileGetLine(i);

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
	}
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

void TextParser::GetWordBlocks(std::vector<std::string> WordBlocks, const std::string LineContents)
{
	//http://www.boost.org/doc/libs/1_64_0/doc/html/string_algo/usage.html#idp124639424
	/// Essa funcao ao receber os parametros eles seriam ByVal ou ByRef?
	char C;
	// Loop Characters of LineContents
	for (unsigned int i = 0; i < LineContents.length(); i++)
	{
		C = LineContents.at(i);
		if (!CharIsWS(C))
		{
		// If found NL, CR, Enter, ect, What do?
		// Found first non WS (Whitespace)
			// If the WordBlock starts with "
				// WordBlock is string and ends at next " unless it is escaped \"
				// Escaped: \\ or \" otherwise --> error. eg: \P --> \\P
			// If the WordBlock doesn't start with "
				// Ends with first WS after WordBlock
			// Pushback this WordBlock
		}
	}
}


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
	/**
	Returns:
		0 = All is Good
		1 = ifstream file = fail or bad
	/**/
}