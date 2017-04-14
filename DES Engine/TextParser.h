#pragma once
#include <fstream>
#include <string>
#include <vector>

class TextParser
{
public:
	TextParser(std::string Filename);
	TextParser();
	~TextParser();

	void LoadFileLines(std::string Filename);

private:
	// flin = File Lines
	std::vector<std::string> flin;
};

