// Bruno Osorio Oliveira dos Santos
// Homework Assignment 5
// WordFont Assignment
// CIS 554

#include <iostream>
#include <string>
#include "WordFont.h"

// Function to produce every letter possible by the font.
// The main function can be modified to call this function
// to get all characters, bolded or not, in every size.
// Since this functions outputs a lot of stuff, it would be
// better to redirect the output to a file via command line.
// The file "test.txt" that comes along with the zip file
// contains the output of this function as file.
void testAll();

int main(int argc, char* args[])
{
    if (argc > 1 && std::string(args[1]) == std::string("test"))
    {
        testAll();
        return 0;
    }

	WordFont font;
	std::string userInput; // First input from user - the string he wants to print.
	char drawingCharacter; // Second input from user - the character used to draw the letters
	int fontSize; // Third input from user - the size of the font
	int boldMode; // Fourth input from user - how the font will be bolded

	// Ask for inputs
	font.askStringInput(userInput);
	font.askDrawingCharacterInput(drawingCharacter);
	font.askFontSizeInput(fontSize);
	font.askBoldedInput(boldMode);

	std::cout << "\n";

	font.drawWord(userInput, drawingCharacter, fontSize, 2, boldMode);
	font.print();

	std::cout << "\nPress enter to exit...";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();

	return 0;
}

void testAll()
{
	WordFont word;
	std::string string;

    // Builds a string with the entire alphabet
    // in lower and upper cases: AaBbCc...Zz
	for (char c = 'A'; c <= 'Z'; c++)
	{
		if (word.canDrawLetter(c))
			string = string + c + (char)(c + 32);
	}

    // Prints it with fonts size 8, 9, 10, 11 and 12.
    // Outputting to console ends up in word wrapping
    // and result can't be observed. Better set
    // stdout to a file before running this function.
	for (int i = 8; i <= 12; i++)
	{
		std::cout << "Character size: " << i << ", word: " << string << "\n\n";
		word.drawWord(string, 'X', i, 4, 2);
		word.print();
		std::cout << "\n";
	}
}
