// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2017

#ifndef TXTPAR
#define TXTPAR

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
	int LoadLines(const std::string &Filename);

	// Returns the total line count
	const unsigned int GetLineCount();

	const std::string GetFilename();

	// LineNumber goes from [1, GetLineCount]
	std::string GetLine(const unsigned int LineNumber);

	// Returns blocks of words from LineContents where comments are ignored until the end
	void GetWordBlocks(std::vector<std::string> &WordBlocks, const std::string &LineContents, const bool AppendpS = false);
		// eg: The quick "/////"brown fox/"" jumps //over the rabbit
		// return: ['The', 'quick', '//"brown fox"', 'jumps']

private:
	// flin = File Lines
	std::vector<std::string> flin;
	std::string TP_Filename;

	// Helper functions for GetWordBlocks
	void IfStringGetString(char &C, std::vector<std::string> &WordBlocks, std::vector<char> &Word, unsigned int &i, int &Ctrl, const std::string &LineContents, const bool AppendpS = false);
	void IfCommentSetCtrl(char &C, const std::string & LineContents, unsigned int &i, int &Ctrl);
	bool IsCharWS(const char C);

};

#endif