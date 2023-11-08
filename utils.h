#pragma once
#include <string>
#include <iostream>
using namespace std;

// Function to convert a string to lowercase
string toLowerCase(string input)
{
	// Iterate through each character in the string
	for (std::string::size_type i = 0; i < input.length(); i++)
	{
		// Check if the character is within the ASCII range for uppercase letters
		if (input[i] >= 65 && input[i] <= 90) // ASCII range for uppercase letters is 65 to 90
		{
			// Convert the character to lowercase by adding the ASCII difference
			// ('A' is 65, 'a' is 97, so adding 32 converts uppercase to lowercase)
			input[i] += 32;
		}
	}
	// Return the converted string
	return input;
}

// Function to print a line as a prompt for the SQL interface
void printLine()
{
	// Print the SQL prompt with a newline character
	cout << "\nsqlight> ";
}
