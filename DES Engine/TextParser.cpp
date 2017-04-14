#include "TextParser.h"


TextParser::TextParser(std::string Filename)
{
	LoadFileLines(Filename);
}

TextParser::TextParser()
{
}

TextParser::~TextParser()
{
}

void TextParser::LoadFileLines(std::string Filename)
{
	std::ifstream file(Filename);
	std::string str;

	// Is this if condition correct?
	if (!file && !file.good()) { throw std::ios_base::failure("File could not be opened"); return; }

	flin.clear();

	while (std::getline(file, str))
	{
		flin.push_back(str);
	}

	file.close();

	return;
}