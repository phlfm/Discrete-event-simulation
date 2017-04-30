// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - April 2017

#pragma once
#include <fstream>
#include <string>
#include <vector>



class TextParser
{
public:
	TextParser(const std::string &Filename);
	TextParser();
	~TextParser();

	// Opens, reads and retrieves file lines
	// return	0: read ok
	//			1: could not open stream
	int FileLoadLines(const std::string &Filename);

	// Returns the total line count
	unsigned int FileLineCount();

	std::string TextParser::GetFilename();

	// LineNumber goes from [1, FileLineCount]
	std::string FileGetLine(const unsigned int LineNumber);

	// Returns blocks of words from LineContents where comments are ignored until the end
	void TextParser::GetWordBlocks(std::vector<std::string> &WordBlocks, const std::string &LineContents, const bool AppendpS = false);
		// eg: The quick "//brown fox" jumps //over the rabbit
		// return: ["The", "quick", "//brown fox", "jumps"]

private:
	// flin = File Lines
	std::vector<std::string> flin;
	std::string TP_Filename;

	// Helper functions for GetWordBlocks
	void TextParser::IfStringGetString(char &C, std::vector<std::string> &WordBlocks, std::vector<char> &Word, unsigned int &i, int &Ctrl, const std::string &LineContents, const bool AppendpS = false);
	void TextParser::IfCommentSetCtrl(char &C, const std::string & LineContents, unsigned int &i, int &Ctrl);
	bool TextParser::IsCharWS(const char C);

};

