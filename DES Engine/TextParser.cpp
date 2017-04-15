// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#include "TextParser.h"


TextParser::TextParser(const char* Filename)
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

std::string TextParser::FileGetLine(unsigned int LineNumber)
{
	return flin.at(LineNumber);
}

int TextParser::FileLoadLines(const char* Filename)
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