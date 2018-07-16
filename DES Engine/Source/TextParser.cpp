// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018
// C++ Core "Standard" by Bjarne Stroustrup: https://goo.gl/4bziNu

#include "TextParser.h"
#define _HTab	9  // Horizontal Tab
#define _NL		10 // New line or LF = line feed
#define _VTab	11 // Vertical Tab
#define _CR		13 // Carriage Return
#define _Space	32 // 
#define _Quote  34 // "
#define _FSlash 47 // /
#define _BSlash 92 // \

using namespace DESE;

TextParser::TextParser(const std::string &Filename)
{
	LoadLines(Filename);
}

TextParser::TextParser()
{
}

TextParser::~TextParser()
{
}

#pragma region Getters
const unsigned int TextParser::GetLineCount()
{
	return flin.size();
}

// LineNumber goes from [1, GetLineCount]
std::string TextParser::GetLine(const unsigned int LineNumber)
{
	return flin.at(LineNumber - 1);
}

const std::string TextParser::GetFilename()
{
	return TP_Filename;
}
#pragma endregion

// Opens, reads and retrieves file lines
void TextParser::LoadLines(const std::string &Filename)
{
	TP_Filename = Filename;

	std::ifstream file(Filename, std::ifstream::in);
	std::string str {""};

	
	if (!file) { file.close(); throw std::runtime_error("TextParser::LoadLines: Could not open file '" + Filename + "'"); }

	flin.clear();

	// Push back file lines while available
	while (std::getline(file, str))
	{
		flin.push_back(str);
	}

	file.close();

	flin.shrink_to_fit();

	return;
}


void TextParser::GetWordBlocks(std::vector<std::string> &WordBlocks, const std::string &LineContents, const bool AppendpS)
{
	///http://www.boost.org/doc/libs/1_64_0/doc/html/string_algo/usage.html#idp124639424

	char C = 0;
	int Ctrl = 0; // Control Flag: 1 = Found Word, 2 Found String, -1 = Comment
	std::vector<char> Word;

	WordBlocks.clear();

	// Loop Characters of LineContents while Ctrl != -1 (comment)
	for (unsigned int i = 0; i < LineContents.length() && (Ctrl != -1); i++)
	{
		C = LineContents.at(i);

		if (!IsCharWS(C)) // Found first non WS (Whitespace)
		{
			// If the WordBlock starts with " --> It is a string
			IfStringGetString(C, WordBlocks, Word, i, Ctrl, LineContents, AppendpS);

			// Is it a comment?
			IfCommentSetCtrl(C, LineContents, i, Ctrl);

			// Word Found --> Not string, not comment
			if (Ctrl == 0 || Ctrl == 1)
			{
				Word.push_back(C);
				Ctrl = 1;
			}

			// String end, on next loop look for more params
			if (Ctrl == 2) { Ctrl = 0; }

		}
		else {
			if (Ctrl == 1)
			{
				// Word found and new WS found --> end of Word
				WordBlocks.push_back(std::string(Word.begin(), Word.end()));
				Word.clear();
				Ctrl = 0;
			}
			else {
				// If found NL, CR --> Unexpected
				if (C == _NL || C == _CR) { throw std::exception::exception("Unexpected Char"); }
			}
		}
	}

	// End of character loop
	if (Ctrl == 1)
	{
		// Word found and end of linecontents --> end of Word
		WordBlocks.push_back(std::string(Word.begin(), Word.end()));
		Word.clear();
	}
}

#pragma region Helper Functions for GetWordBlocks
inline void TextParser::IfStringGetString(char &C, std::vector<std::string> &WordBlocks, std::vector<char> &Word, unsigned int &i, int &Ctrl, const std::string &LineContents, const bool AppendpS)
{
	if (C == _Quote && Ctrl == 0)
	{
		Ctrl = 2; // Found String
				  // Look for end of string (")
		for (unsigned int j = (i+1); j < LineContents.length(); j++)
		{
			C = LineContents.at(j);

			// Escape apropriate characters
			while (C == _BSlash)
			{
				// 1 2 3 4 5 6 7
				// / / / " T X T
				j++; C = LineContents.at(j); // j points to 1. Increment and check position 2. Add Pos(2) to Word vector.
				j++; // Increment and point to Pos(3)

					 // Escaped is \\ or \" otherwise --> error. eg: \P --> \\P
				switch (C)
				{
				case _BSlash:
					Word.push_back(C); break;
				case _Quote:
					Word.push_back(C); break;
				default:
					throw std::exception::exception("Unexpected escape character"); break;
				}
			}

			// End of String
			if (C == _Quote)
			{
				if (AppendpS) // Appends s% to the start of the WordBlock
				{
					Word.insert(Word.begin(), '%');
					Word.insert(Word.begin(),'s');

				}
				i = j;
				WordBlocks.push_back(std::string(Word.begin(), Word.end()));
				Word.clear();
				break;
			}

			// Add C to string element
			Word.push_back(C);

		}
	}
	return;
}

inline void TextParser::IfCommentSetCtrl(char &C, const std::string & LineContents, unsigned int &i, int &Ctrl)
{
	if (C == _FSlash)
	{
		// If we have two // in a row
		if (LineContents.at(i+1) == _FSlash)
		{
			// It is a comment
			Ctrl = -1;
		}
	}
}

inline bool TextParser::IsCharWS(const char C)
{
	if (C == _HTab || C == _NL || C == _VTab || C == _CR || C == _Space) { return true; }
	return false;
}
#pragma endregion
