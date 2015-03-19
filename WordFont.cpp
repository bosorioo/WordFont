// Bruno Osorio Oliveira dos Santos
// Homework Assignment 5
// WordFont Assignment
// CIS 554

#include "WordFont.h"
#include <iostream>

#define MAX_STRING_LENGTH 20
#define MIN_FONT_SIZE 8
#define MAX_FONT_SIZE 12

void WordFont::askStringInput(std::string& out_str)
{
	std::cout << "Enter a string (max. of " << MAX_STRING_LENGTH << " letters) using the following characters: [";

	// Tell user possible characters and asks for a string
	coutPossibleCharset();

	std::cout << "] -> ";

	bool firstTimeAsking = true;
	char buffer[256];

	// Keep getting input until it is acceptable
	do
	{
		if (firstTimeAsking)
			firstTimeAsking = false;
		else
			std::cout << "There are invalid characters in that string. Please retype it: ";

		std::cin.get(buffer, sizeof(buffer) / sizeof(*buffer));
		std::cin.clear();
		std::cin.ignore(std::string::npos, '\n');
		std::cin.sync();
		out_str = buffer;

	} while (!isValidInputString(out_str));

	// Chop string if it is too big
	if (out_str.size() > MAX_STRING_LENGTH)
	{
		out_str.resize(MAX_STRING_LENGTH);
		std::cout << "Your input was too big, so it's substring of length " << MAX_STRING_LENGTH << " will be used instead.\n";
	}
}

void WordFont::askDrawingCharacterInput(char& out_char)
{
	// Ask and get input
	std::cout << "Enter the pixel character you want to use to draw: ";
	std::cin >> out_char;
	std::cin.clear();
	std::cin.ignore(std::string::npos, '\n');
	std::cin.sync();
}

void WordFont::askFontSizeInput(int& out_int)
{
	// Ask and get third input
	std::cout << "Enter the font size (" << MIN_FONT_SIZE << "-" << MAX_FONT_SIZE << "): ";
	std::cin >> out_int;
	std::cin.clear();
	std::cin.ignore(std::string::npos, '\n');
	std::cin.sync();

	// Keep asking until input is correct
	while (out_int < MIN_FONT_SIZE || out_int > MAX_FONT_SIZE)
	{
		std::cout << "The font size must be between " << MIN_FONT_SIZE << " and " << MAX_FONT_SIZE << ", please reenter font size: ";
		std::cin >> out_int;
		std::cin.clear();
		std::cin.ignore(std::string::npos, '\n');
	}
}

void WordFont::askBoldedInput(int& out_int)
{
	// Ask and get input
	std::cout << "Bold? (0 = No, 1 = Yes, 2 = Uppercase characters will be bolded and lowercase won't): ";
	std::cin >> out_int;
	std::cin.clear();
	std::cin.ignore(std::string::npos, '\n');
	std::cin.sync();

	// Keep asking until input is correct
	while (out_int < 0 || out_int > 2)
	{
		std::cout << "Please answer 0, 1 or 2: ";
		std::cin >> out_int;
		std::cin.clear();
		std::cin.ignore(std::string::npos, '\n');
	}

}

void WordFont::coutPossibleCharset()
{
	bool first = true;

	// For every letter
	for (char c = 'a'; c <= 'z'; c++)
	{
		// Check if it can be drawn and prints it
		if (canDrawLetter(c))
		{
			if (first)
				first = false;
			else
				std::cout << ", ";

			std::cout << c;
		}
	}
}

bool WordFont::canDrawLetter(char letter)
{
	drawLetterFunction function; // Pointer to which method will be used to draw the letter.
	getDrawFunction(letter, function); // Get the pointer to the method to draw the letter.
	return function != NULL || letter == ' '; // If there is a method to draw the letter, or it is a space, it is drawable.
}

void WordFont::drawWord(std::string word, char drawingChar, int fontSize, int spacing, int boldMode)
{
	setFrameSize(fontSize, (fontSize + spacing) * word.size() - spacing); // Resize the entire picture (initially blank after resizing).

	drawLetterFunction function; // Pointer to which method will be used to draw the letter.

	int row = 0; // Position where the letter will be drawn.
	int col = 0; // Position where the letter will be drawn.

	// Iterate for each character in the string
	for (std::string::iterator it = word.begin(); it != word.end(); it++)
	{
		// Obtain the method of this class that can draw that letter and
		// write the pointer to the method in the variable 'function'.
		getDrawFunction(*it, function);

		// If function is a valid pointer:
		if (function != NULL)
			// Run the given method with the correct parameters.
			(this->*function)(drawingChar, row, col, fontSize, boldMode == 1 || (*it <= 'Z' && boldMode == 2));

		col += fontSize + spacing; // Adjust position for next letter.
	}
}

void WordFont::print()
{
	std::vector< std::vector<char> >::iterator rowIt; // To iterate over rows
	std::vector<char>::iterator colIt; // To iterate over collumns

	// Iterates over all rows
	for (rowIt = m_frame.begin(); rowIt != m_frame.end(); rowIt++)
	{
		// Iterates over all collumns of the outer loop current row
		for (colIt = rowIt->begin(); colIt != rowIt->end(); colIt++)
			std::cout << *colIt; // Print value held by each element in the vector (all collumns)

		std::cout << std::endl; // New line after finishing each row
	}
}

bool WordFont::isValidInputString(std::string& str)
{
	// Iterates the string looking for an invalid letter
	for (std::string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (!canDrawLetter(*it)) // Returns false if it can't be drawn
			return false;
	}

	// Returns true if every character is acceptable
	return true;
}

bool WordFont::isValidCoordinate(int row, int col)
{
	// Coordinates start at 0 and goes until (size - 1).
	// This return whether that coordinate is inside the bounds of the 2d-vector.
	return row >= 0 && col >= 0 && row < (int)m_frame.size() && col < (int)m_frame[0].size();
}

void WordFont::setFrameSize(int rows, int collumns)
{
	m_frame.clear(); // Clear matrix
	// Creates the correct numbers of rows, each one having a vector of the correct number of
	// collumns with every character initiated to space.
	m_frame.resize(rows, std::vector<char>(collumns, ' '));
}

void WordFont::drawLine(char drawChar, int row, int col, int length, bool vertical)
{
	while (length-- > 0) // Repeats until length is down to 0
	{
		if (isValidCoordinate(row, col)) // Check if coordinates are inside bounds
			m_frame[row][col] = drawChar; // Draw character to matrix

		vertical ? row++ : col++; // Increment the correct coordinate depending on the line orientation
	}
}

void WordFont::drawDiagonal(char drawChar, int row, int col, int length, bool ascending)
{
	while (length-- > 0) // Repeats until length is down to 0
	{
		if (isValidCoordinate(row, col)) // Check if coordinates are inside bounds
			m_frame[row][col] = drawChar; // Draw character to matrix

		col++; // Diagonal always goes to the right
		ascending ? row-- : row++; // If the diagonal is ascending, next character must be higher, otherwise goes lower.
	}
}

void WordFont::getDrawFunction(char letter, drawLetterFunction& out_ptr)
{
	// Try to match a letter with it's corresponding method.
	switch (letter)
	{
		case 'a': case 'A': out_ptr = &WordFont::drawA; break;
		case 'b': case 'B': out_ptr = &WordFont::drawB; break;
		case 'c': case 'C': out_ptr = &WordFont::drawC; break;
		case 'd': case 'D': out_ptr = &WordFont::drawD; break;
		case 'e': case 'E': out_ptr = &WordFont::drawE; break;
		case 'f': case 'F': out_ptr = &WordFont::drawF; break;
		case 'g': case 'G': out_ptr = &WordFont::drawG; break;
		case 'h': case 'H': out_ptr = &WordFont::drawH; break;
		case 'i': case 'I': out_ptr = &WordFont::drawI; break;
		case 'j': case 'J': out_ptr = &WordFont::drawJ; break;
		case 'k': case 'K': out_ptr = &WordFont::drawK; break;
		case 'l': case 'L': out_ptr = &WordFont::drawL; break;
		case 'm': case 'M': out_ptr = &WordFont::drawM; break;
		case 'n': case 'N': out_ptr = &WordFont::drawN; break;
		case 'o': case 'O': out_ptr = &WordFont::drawO; break;
		case 'p': case 'P': out_ptr = &WordFont::drawP; break;
		case 'q': case 'Q': out_ptr = &WordFont::drawQ; break;
		case 'r': case 'R': out_ptr = &WordFont::drawR; break;
		case 's': case 'S': out_ptr = &WordFont::drawS; break;
		case 't': case 'T': out_ptr = &WordFont::drawT; break;
		case 'u': case 'U': out_ptr = &WordFont::drawU; break;
		case 'v': case 'V': out_ptr = &WordFont::drawV; break;
		case 'w': case 'W': out_ptr = &WordFont::drawW; break;
		case 'x': case 'X': out_ptr = &WordFont::drawX; break;
		case 'y': case 'Y': out_ptr = &WordFont::drawY; break;
		case 'z': case 'Z': out_ptr = &WordFont::drawZ; break;

		default: out_ptr = NULL; break;
	}
}

void WordFont::drawA(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + 1, col, fontSize - 1, true);
	drawLine(drawChar, row + 1, col + fontSize - 1, fontSize - 1, true);
	drawLine(drawChar, row + fontSize / 2, col + 1, fontSize - 2, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 2, fontSize - 4, false);
		drawLine(drawChar, row + 1 + fontSize / 2, col + 2, fontSize - 4, false);
		drawLine(drawChar, row + 1, col + 1, fontSize - 1, true);
		drawLine(drawChar, row + 1, col + fontSize - 2, fontSize - 1, true);
	}
}

void WordFont::drawB(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int topArcLength = (fontSize - 3) / 2;
	int botArcLength = fontSize - 3 - topArcLength;
	int botRescue = 1 + (botArcLength > 2);
	int topRescue = botRescue + (topArcLength > 2);

	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 1 - botRescue, false);
	drawLine(drawChar, row + 1 + topArcLength, col + 1, fontSize - 1 - botRescue, false);
	drawLine(drawChar, row, col + 1, fontSize - 1 - topRescue, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 2, true);
		drawLine(drawChar, row + fontSize - 2, col + 2, fontSize - 3 - botRescue, false);
		drawLine(drawChar, row + 2 + topArcLength, col + 2, fontSize - 3 - botRescue, false);
		drawLine(drawChar, row + 1, col + 2, fontSize - 3 - topRescue, false);
	}

	if (topArcLength <= 2)
	{
		drawLine(drawChar, row + 1, col + fontSize - topRescue, topArcLength, true);

		if (isBold)
			drawLine(drawChar, row + 1, col + fontSize - topRescue - 1, topArcLength, true);
	}
	else
	{
		drawLine(drawChar, row + 1, col + fontSize - topRescue - isBold, 1 + isBold, false);
		drawLine(drawChar, row + topArcLength, col + fontSize - topRescue - isBold, 1 + isBold, false);
		drawLine(drawChar, row + 2, col + fontSize - topRescue + 1, topArcLength - 2, true);

		if (isBold)
			drawLine(drawChar, row + 2, col + fontSize - topRescue, topArcLength - 2, true);
	}

	if (botArcLength <= 2)
	{
		drawLine(drawChar, row + topArcLength + 2, col + fontSize - botRescue, botArcLength, true);

		if (isBold)
			drawLine(drawChar, row + topArcLength + 2, col + fontSize - botRescue - 1, botArcLength, true);
	}
	else
	{
		drawLine(drawChar, row + topArcLength + 2, col + fontSize - botRescue - isBold, 1 + isBold, false);
		drawLine(drawChar, row + topArcLength + botArcLength + 1, col + fontSize - botRescue - isBold, 1 + isBold, false);
		drawLine(drawChar, row + topArcLength + 3, col + fontSize - botRescue + 1, botArcLength - 2, true);

		if (isBold)
			drawLine(drawChar, row + topArcLength + 3, col + fontSize - botRescue, botArcLength - 2, true);
	}
}

void WordFont::drawC(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row + 2, col, fontSize - 4, true);
	drawLine(drawChar, row, col + 2, fontSize - 2, false);
	drawLine(drawChar, row + fontSize - 1, col + 2, fontSize - 2, false);

	drawLine(drawChar, row + 1, col + 1, isBold ? fontSize - 1 : 1, false);
	drawLine(drawChar, row + fontSize - 2, col + 1, isBold ? fontSize - 1 : 1, false);

	if (isBold)
		drawLine(drawChar, row + 2, col + 1, fontSize - 4, true);
}

void WordFont::drawD(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row + 2, col + fontSize - 1, fontSize - 4, true);
	drawLine(drawChar, row, col + 1, fontSize - 3, false);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 3, false);
	drawLine(drawChar, row + 1, col + fontSize - 2, 1, false);
	drawLine(drawChar, row + fontSize - 2, col + fontSize - 2, 1, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 3, false);
		drawLine(drawChar, row + fontSize - 2, col + 1, fontSize - 3, false);
		drawLine(drawChar, row + 2, col + 1, fontSize - 4, true);
		drawLine(drawChar, row + 2, col + fontSize - 2, fontSize - 4, true);
	}
}

void WordFont::drawE(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + fontSize/2, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 1, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 2, true);
		drawLine(drawChar, row + 1, col + 2, fontSize - 3, false);
		drawLine(drawChar, row + fontSize/2 - 1, col + 2, fontSize - 3, false);
		drawLine(drawChar, row + fontSize - 2, col + 2, fontSize - 2, false);
	}
}

void WordFont::drawF(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + 1, fontSize - 1, false);
	drawLine(drawChar, row + (fontSize - 1) / 2, col + 1, fontSize - 2, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 1, true);
		drawLine(drawChar, row + 1, col + 2, fontSize - 2, false);
		drawLine(drawChar, row + (fontSize - 1) / 2 + 1, col + 2, fontSize - 3, false);
	}
}

void WordFont::drawG(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int middleRow = (fontSize + 1) / 2;

	drawLine(drawChar, row, col + 2, fontSize - 2, false);
	drawLine(drawChar, row + 1, col + 1, isBold ? fontSize - 1 : 1, false);
	drawLine(drawChar, row + 2, col, fontSize - 4, true);
	drawLine(drawChar, row + fontSize - 2, col + 1, isBold ? fontSize - 2 : 1, false);
	drawLine(drawChar, row + fontSize - 1, col + 2, fontSize - 2, false);
	drawLine(drawChar, row + middleRow, col + 3, fontSize - 3, false);
	drawLine(drawChar, row + middleRow + 1, col + fontSize - 1, fontSize / 2, true);

	if (isBold)
	{
		drawLine(drawChar, row + 2, col + 1, fontSize - 4, true);
		drawLine(drawChar, row + middleRow + 1, col + fontSize - 2, fontSize - middleRow - 3, true);
	}
}

void WordFont::drawH(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + fontSize - 1, fontSize, true);
	drawLine(drawChar, row + (fontSize - 1) / 2, col + 1, fontSize - 2, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize, true);
		drawLine(drawChar, row, col + fontSize - 2, fontSize, true);
		drawLine(drawChar, row + (fontSize - 1) / 2 + 1, col + 2, fontSize - 4, false);
	}
}

void WordFont::drawI(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, false);
	drawLine(drawChar, row + fontSize - 1, col, fontSize, false);
	drawLine(drawChar, row + 1, col + (fontSize - 1) / 2, fontSize - 2, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col, fontSize, false);
		drawLine(drawChar, row + fontSize - 2, col, fontSize, false);
		drawLine(drawChar, row + 2, col + (fontSize - 1) / 2 + 1 - 2 * (fontSize % 2), fontSize - 4, true);
	}
}

void WordFont::drawJ(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int space = fontSize / 4;

	drawLine(drawChar, row, col, fontSize, false);
	drawLine(drawChar, row + 1, col + (fontSize - 1) - space, fontSize - 2, true);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 2 - space, false);
	drawLine(drawChar, row + fontSize - 1 - space, col, space, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col, fontSize, false);
		drawLine(drawChar, row + 2, col + (fontSize - 1) - space - 1, fontSize - 4, true);
		drawLine(drawChar, row + fontSize - 2, col + 1, fontSize - 2 - space, false);
	}
}

void WordFont::drawK(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int middle = (fontSize - 1) / 2;

	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row + middle, col + 1, middle, false);
	drawDiagonal(drawChar, row + middle - 1, col + middle + 1, middle, true);
	drawDiagonal(drawChar, row + middle + 1, col + middle + 1, fontSize - 1 - middle, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize, true);
		drawLine(drawChar, row + middle + 1, col + 2, middle - 1, false);
		drawDiagonal(drawChar, row + middle - 1, col + middle, middle, true);
		drawDiagonal(drawChar, row + middle + 1, col + middle, fontSize - 1 - middle, false);
	}
}

void WordFont::drawL(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 1, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize, true);
		drawLine(drawChar, row + fontSize - 2, col + 2, fontSize - 2, false);
	}
}

void WordFont::drawM(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row + 1, col, fontSize - 1, true);
	drawLine(drawChar, row + 1, col + fontSize - 1, fontSize - 1, true);
	drawDiagonal(drawChar, row, col, fontSize / 2 + (fontSize % 2), false);
	drawDiagonal(drawChar, row + fontSize / 2 - 1, col + fontSize / 2 + (fontSize % 2), fontSize / 2, true);

	if (isBold)
	{
		drawLine(drawChar, row + 3, col + 1, fontSize - 3, true);
		drawLine(drawChar, row + 3, col + fontSize - 2, fontSize - 3, true);
		drawDiagonal(drawChar, row + 2, col + 1, fontSize / 2 + (fontSize % 2) - 1, false);
		drawDiagonal(drawChar, row + fontSize / 2, col + fontSize / 2 + (fontSize % 2), fontSize / 2 - 1, true);
	}
}

void WordFont::drawN(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + fontSize - 1, fontSize, true);
	drawDiagonal(drawChar, row + 1, col + 1, fontSize - 2, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize, true);
		drawLine(drawChar, row, col + fontSize - 2, fontSize, true);
		drawDiagonal(drawChar, row, col + 1, fontSize - 2, false);
	}
}

void WordFont::drawO(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + 1, col, fontSize - 2, true);
	drawLine(drawChar, row + 1, col + fontSize - 1, fontSize - 2, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 2, false);
		drawLine(drawChar, row + fontSize - 2, col + 1, fontSize - 2, false);
		drawLine(drawChar, row + 2, col + 1, fontSize - 4, true);
		drawLine(drawChar, row + 2, col + fontSize - 2, fontSize - 4, true);
	}
}

void WordFont::drawP(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + (fontSize - 1) / 2, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + 1, col + fontSize - 1, (fontSize - 1) / 2 - 1 + isBold, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 1, true);
		drawLine(drawChar, row + 1, col + fontSize - 2, (fontSize - 1) / 2 - 1, true);
		drawLine(drawChar, row + 1, col + 2, fontSize - 4, false);
		drawLine(drawChar, row + (fontSize - 1) / 2 + 1, col + 2, fontSize - 3, false);
	}
}

void WordFont::drawQ(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col + 1, fontSize - 3, false);
	drawLine(drawChar, row + fontSize - 2, col + 1, fontSize - 3, false);
	drawLine(drawChar, row + 1, col, fontSize - 3, true);
	drawLine(drawChar, row + 1, col + fontSize - 2, fontSize - 3, true);
	drawDiagonal(drawChar, row + fontSize / 2 + (fontSize % 2), col + fontSize / 2 + (fontSize % 2), fontSize / 2, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 3, false);
		drawLine(drawChar, row + fontSize - 3, col + 1, fontSize - 3, false);
		drawLine(drawChar, row + 2, col + 1, fontSize - 5, true);
		drawLine(drawChar, row + 2, col + fontSize - 3, fontSize - 5, true);
		drawDiagonal(drawChar, row + fontSize / 2 + (fontSize % 2), col + fontSize / 2 + (fontSize % 2) - 1, fontSize / 2, false);
	}
}

void WordFont::drawR(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int space = (fontSize - 1) / 2;

	drawLine(drawChar, row + 1, col, fontSize - 1, true);
	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + space, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + 1, col + fontSize - 1,space - 1, true);
	drawDiagonal(drawChar, row + space + 1, col + space + 1, fontSize - 1 - space, false);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 1, true);
		drawLine(drawChar, row + 1, col + 2, fontSize - 4, false);
		drawLine(drawChar, row + space + 1, col + 2, fontSize - 4, false);
		drawLine(drawChar, row + 1, col + fontSize - 2,space - 1, true);
		drawDiagonal(drawChar, row + space + 1, col + space, fontSize - 1 - space, false);
	}
}

void WordFont::drawS(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int half = (fontSize - 1) / 2 - 1;

	drawLine(drawChar, row, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + 1, col, half + isBold, true);
	drawLine(drawChar, row + half + 1, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + half + 2, col + fontSize - 1, half + (fontSize % 2 == 0), true);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 2, false);
	drawLine(drawChar, row + fontSize - 1 - half / 2, col, half / 2, true);
	drawLine(drawChar, row + 1, col + fontSize - 1, half / 2, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col + 1, fontSize - 2, false);
		drawLine(drawChar, row + 2, col + 1, half - 1, true);
		drawLine(drawChar, row + half + 2, col + 1, fontSize - 2, false);
		drawLine(drawChar, row + half + 3, col + fontSize - 2, half + (fontSize % 2 == 0) - 2, true);
		drawLine(drawChar, row + fontSize - 2, col + 1, fontSize - 2, false);
	}
}

void WordFont::drawT(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize, false);
	drawLine(drawChar, row + 1, col + (fontSize - 1) / 2, fontSize - 1, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col, fontSize, false);
		drawLine(drawChar, row + 2, col + (fontSize - 1) / 2 + 1 - 2 * (fontSize % 2), fontSize - 2, true);
	}
}

void WordFont::drawU(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize - 1, true);
	drawLine(drawChar, row, col + fontSize - 1, fontSize - 1, true);
	drawLine(drawChar, row + fontSize - 1, col + 1, fontSize - 2, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize - 1, true);
		drawLine(drawChar, row, col + fontSize - 2, fontSize - 1, true);
		drawLine(drawChar, row + fontSize - 2, col + 2, fontSize - 4, false);
	}
}

void WordFont::drawV(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int length = fontSize / 2;

	drawLine(drawChar, row, col, fontSize - length, true);
	drawLine(drawChar, row, col + fontSize - 1, fontSize - length, true);
	drawDiagonal(drawChar, row + length, col, length + (fontSize % 2), false);
	drawDiagonal(drawChar, row + fontSize - 1 - (fontSize % 2), col + length + (fontSize % 2), length, true);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize - length, true);
		drawLine(drawChar, row, col + fontSize - 2, fontSize - length, true);
		drawDiagonal(drawChar, row + length, col + 1, length, false);
		drawDiagonal(drawChar, row + fontSize - 2 - (fontSize % 2), col + length + (fontSize % 2), length, true);
	}
}

void WordFont::drawW(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int length = (fontSize - 1) / 2;
	int even = (fontSize % 2) == 0;

	drawLine(drawChar, row, col, fontSize, true);
	drawLine(drawChar, row, col + fontSize - 1, fontSize, true);
	drawDiagonal(drawChar, row + fontSize - 1, col + 1, length, true);
	drawDiagonal(drawChar, row + fontSize - length, col + length + even, length, false);

	if (isBold)
	{
		drawLine(drawChar, row, col + 1, fontSize, true);
		drawLine(drawChar, row, col + fontSize - 2, fontSize, true);
		drawDiagonal(drawChar, row + fontSize - 1, col, length - even, true);
		drawDiagonal(drawChar, row + fontSize - length + even, col + length + 2 * even + 1, length - even, false);

		if (!even)
			drawLine(drawChar, row + length, col + length, 1, true);
	}

}

void WordFont::drawX(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawDiagonal(drawChar, row, col, fontSize, false);
	drawDiagonal(drawChar, row + fontSize - 1, col, fontSize, true);

	if (isBold)
	{
		drawDiagonal(drawChar, row, col + 1, fontSize - 1, false);
		drawDiagonal(drawChar, row + fontSize - 2, col, fontSize - 1, true);
		drawDiagonal(drawChar, row + fontSize - 1, col + 1, 1, true);
		drawDiagonal(drawChar, row + fontSize - 1, col + fontSize - 2, 1, true);
	}
}

void WordFont::drawY(char drawChar, int row, int col, int fontSize, bool isBold)
{
	int length = fontSize / 2;
	int odd = fontSize % 2;

	drawDiagonal(drawChar, row, col, length, false);
	drawDiagonal(drawChar, row + length - 1, col + length + odd, length, true);
	drawLine(drawChar, row + length, col + (fontSize - 1) / 2, length, true);

	if (isBold)
	{
		drawDiagonal(drawChar, row + 1, col, length - 1, false);
		drawDiagonal(drawChar, row + length, col + length + odd, length, true);
		drawLine(drawChar, row + length, col + (fontSize - 1) / 2 + 1, length, true);
		drawLine(drawChar, row, col + 1, 1, true);
		drawLine(drawChar, row, col + fontSize - 2, 1, true);

		if (odd)
			drawLine(drawChar, row + length, col + (fontSize - 1) / 2 - 1, length, true);
	}
}

void WordFont::drawZ(char drawChar, int row, int col, int fontSize, bool isBold)
{
	drawLine(drawChar, row, col, fontSize , false);
	drawLine(drawChar, row + fontSize - 1, col, fontSize, false);
	drawDiagonal(drawChar, row + fontSize - 1, col, fontSize, true);

	if (isBold)
	{
		drawLine(drawChar, row + 1, col, fontSize , false);
		drawLine(drawChar, row + fontSize - 2, col, fontSize, false);
		drawDiagonal(drawChar, row + fontSize - 2, col, fontSize - 1, true);
	}
}
