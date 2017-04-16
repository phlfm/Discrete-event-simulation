// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <boost/any.hpp>

class TextParser
{
public:
	TextParser(const char *Filename);
	TextParser();
	~TextParser();

	// Opens, reads and retrieves file lines
	// return	0: read ok
	//			1: could not open stream
	int FileLoadLines(const char *Filename);

	// Returns the total line count
	unsigned int FileLineCount();

	// LineNumber goes from [0, FileLineCount - 1]
	std::string FileGetLine(const unsigned int LineNumber);

	void TextParser::GetEventList(std::vector<std::string, std::vector<boost::any>> *EventList);

private:
	// flin = File Lines
	std::vector<std::string> flin;

};
