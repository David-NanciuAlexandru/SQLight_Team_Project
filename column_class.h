#pragma once
#include <iostream>
#include <string>
#include "utils.h" // Importing custom utility functions

using namespace std;

// Enum for different column types, including NUMBER and STRING
enum columnTypes
{
	NUMBER,
	STRING
};

// Column class to represent a database table column
class Column
{
private:
	// Private member variables to store column information
	string columnName = "";									// Name of the column
	columnTypes type = columnTypes::NUMBER; // Type of the column (default: NUMBER)
	size_t size = 0;												// Size of the column
	string defaultValue = "";								// Default value for the column

public:
	// Setter methods for various column attributes
	void setDefaultValue(string input)
	{
		this->defaultValue = input;
	}

	void setColumnName(string input)
	{
		this->columnName = input;
	}

	void setType(columnTypes type)
	{
		this->type = type;
	}

	void setSize(size_t input)
	{
		this->size = input;
	}

	// Getter methods for various column attributes
	string getColumnName()
	{
		return this->columnName;
	}

	size_t getSize()
	{
		return this->size;
	}

	columnTypes getType()
	{
		return this->type;
	}

	string getDefaultValue()
	{
		return this->defaultValue;
	}
};

// Overloading the '<<' operator for the Column class to output column information to the console
void operator<<(ostream &console, Column col)
{
	console << endl
					<< "Column name: " << col.getColumnName(); // Output the column name
	console << endl
					<< "Type: " << col.getType(); // Output the column type
	console << endl
					<< "Size: " << col.getSize(); // Output the column size
	console << endl
					<< "Default: " << col.getDefaultValue(); // Output the default value for the column
	console << endl
					<< "~~~~~~~~~~~~~~~~"; // Divider for readability
}
