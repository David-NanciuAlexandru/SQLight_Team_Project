#pragma once
#include <iostream>
#include <string>
#include "table_class.h"	// Including the header file for the Table class
#include "column_class.h" // Including the header file for the Column class
using namespace std;

// Row class representing a row in a table
class Row
{
	// Private member variables
	int rowId = 0;					// ID of the row
	string *data = nullptr; // Pointer to an array of string data

public:
	// Destructor to deallocate the dynamically allocated memory
	~Row()
	{
		delete[] data; // Deallocating the memory pointed to by 'data'
	}
	// Add more member functions and variables as needed for the Row class
};
