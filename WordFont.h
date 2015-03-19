// Bruno Osorio Oliveira dos Santos
// Homework Assignment 5
// WordFont Assignment
// CIS 554

#ifndef _WORDFONT_H
#define _WORDFONT_H

#include <vector>
#include <string>

class WordFont
{
public:

	void askStringInput(std::string& out_str);
	void askDrawingCharacterInput(char& out_char);
	void askFontSizeInput(int& out_int);
	void askBoldedInput(int& out_it);
	void coutPossibleCharset();
	bool canDrawLetter(char letter);
	void drawWord(std::string word, char drawingChar, int fontSize, int spacing, int boldMode);
	void print();

private:

	typedef void (WordFont::*drawLetterFunction)(char, int, int, int, bool);

	bool isValidInputString(std::string& str);
	bool isValidCoordinate(int row, int col);
	void setFrameSize(int rows, int collumns);
	void drawLine(char drawChar, int row, int col, int length, bool vertical);
	void drawDiagonal(char drawChar, int row, int col, int length, bool ascending);
	void getDrawFunction(char letter, drawLetterFunction& out_ptr);
	void drawA(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawB(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawC(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawD(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawE(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawF(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawG(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawH(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawI(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawJ(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawK(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawL(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawM(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawN(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawO(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawP(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawQ(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawR(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawS(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawT(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawU(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawV(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawW(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawX(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawY(char drawChar, int row, int col, int fontSize, bool isBold);
	void drawZ(char drawChar, int row, int col, int fontSize, bool isBold);

	std::vector< std::vector<char> > m_frame;
};

#endif