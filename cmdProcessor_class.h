// Include necessary libraries
#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "utils.h"
#include "column_class.h"
#include "table_class.h"

// Structure containing the proper formats for different commands
struct properFormats
{
	// Define the proper formats for various commands
	string properCt = "CREATE TABLE table_name [IF NOT EXISTS] ( (column_name1, type, size, default_value1), (column_name1, type, size, default_value1)... )";
	string properCi = "CREATE INDEX [IF NOT EXISTS] index_name ON table_name (column_name) - creates an index only on a single column";
	string properDt = "DROP TABLE table_name";
	string properDi = "DROP INDEX index_name";
	string properDplt = "DISPLAY TABLE table_name";
	string properIi = "INSERT INTO table VALUES(...); values are separated by , and they have the exact number and order as the table definition";
	string properDf = "DELETE FROM table_name WHERE column_name = value (deletes allows only one column in the where clause)";
	string properSt = "SELECT (at_least_one_column, ...) | ALL FROM table_name [WHERE column_name = value] - the where clause is optional";
	string properUe = "UPDATE table_name SET column_name = value WHERE  column_name = value (the SET column may be different than the WHERE one)";
};

// Structure containing regex patterns for different commands
struct regexList
{
	// Define regex patterns for different commands
	string fullCreateTable = "\\s*CREATE\\s+TABLE\\s+([A-Za-z][A-Za-z0-9]+)\\s*(IF\\s+NOT\\s+EXISTS)?\\s+\\(\\s*((?:\\(\\s*[A-Za-z][A-Za-z0-9]+\\s*,\\s*[A-Za-z]+\\s*,\\s*[0-9]+\\s*,\\s*[A-Za-z0-9]+\\s*\\)\\s*,?\\s*)+?)\\s*\\)";
	string fullCreateIndex = "\\s*CREATE\\s+INDEX\\s*(IF\\s+NOT\\s+EXISTS)?\\s+([a-zA-Z0-9]+)\\s+ON\\s+([a-zA-Z0-9]+)\\s+\\((\\s*[a-zA-Z0-9]+)\\s*\\)";
	string fullDropTable = "\\s*DROP\\s+TABLE\\s+([a-zA-Z0-9]+)\\s*";
	string fullDropIndex = "\\s*DROP\\s+INDEX\\s+([a-zA-Z0-9]+)\\s*";
	string fullDisplayTable = "\\s*DISPLAY\\s+TABLE\\s+([a-zA-Z0-9]*)\\s*";
	string fullInsertInto = "\\s*INSERT\\s+INTO\\s+([a-zA-Z0-9]+)\\s+VALUES\\s*\\(((\\s*[a-zA-Z0-9]+\\s*,?\\s*)+)\\)\\s*";
	string fullDeleteFrom = "\\s*DELETE\\s+FROM\\s+([a-zA-Z0-9]+)\\s+WHERE\\s+([a-zA-Z0-9]+)\\s+=\\s+([a-zA-Z0-9]+)\\s*";
	string fullSelect = "\\s*SELECT\\s*((\\((\\s*[a-zA-Z0-9]+\\s*,?\\s*)+\\))+|(ALL))\\s*FROM\\s+([a-zA-Z0-9]+)+\\s*(WHERE\\s+([a-zA-Z0-9]+)\\s*=\\s*([a-zA-Z0-9]+))?";
	string fullUpdate = "\\s*UPDATE\\s+([a-zA-Z0-9]+)\\s+SET\\s+([a-zA-Z0-9]+)\\s*=\\s*([a-zA-Z0-9]+)\\s+WHERE\\s+([a-zA-Z0-9]+)\\s*=\\s*([a-zA-Z0-9]+)\\s*";
};

// Class for processing commands
class CmdProcessor
{
private:
	string fullCmd = "";										 // Stores the full command
	std::vector<std::string> tableList = {}; // List of tables

public:
	// Method to check the validity of a command
	bool checkCmd(TableBuffer &tableBuffer)
	{
		properFormats formats; // Object containing proper command formats
		regexList rlist;			 // Object containing regex patterns for commands

		// Define regex objects for different types of commands
		regex ct("\\s*CREATE\\s+TABLE\\s*", regex::icase);
		regex ci("\\s*CREATE\\s+INDEX\\s*", regex::icase);
		regex dt("\\s*DROP\\s+TABLE\\s*", regex::icase);
		regex di("\\s*DROP\\s+INDEX\\s*", regex::icase);
		regex dplt("\\s*DISPLAY\\s+TABLE\\s*", regex::icase);
		regex ii("\\s*INSERT\\s+INTO\\s*", regex::icase);
		regex df("\\s*DELETE\\s+FROM\\s*", regex::icase);
		regex st("\\s*SELECT\\s*", regex::icase);
		regex ue("\\s*UPDATE\\s*", regex::icase);

		// Define regex objects using the provided patterns
		regex createTableRegex(rlist.fullCreateTable, regex::icase);
		regex createIndexRegex(rlist.fullCreateIndex, regex::icase);
		regex dropTableRegex(rlist.fullDropTable, regex::icase);
		regex dropIndexRegex(rlist.fullDropIndex, regex::icase);
		regex displayTableRegex(rlist.fullDisplayTable, regex::icase);
		regex insertIntoRegex(rlist.fullInsertInto, regex::icase);
		regex deleteFromRegex(rlist.fullDeleteFrom, regex::icase);
		regex selectRegex(rlist.fullSelect, regex::icase);
		regex updateRegex(rlist.fullUpdate, regex::icase);

		smatch matches;

		// Check the full command against each regex pattern and perform corresponding actions
		if (regex_search(this->fullCmd, ct))
		{
			if (regex_search(this->fullCmd, matches, createTableRegex))
			{
				tableBuffer = tableBuffer + *this->createTable(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properCt;
				return 1;
			}
		}
		else if (regex_search(this->fullCmd, ci))
		{
			// Check for CREATE INDEX command
			if (regex_search(this->fullCmd, matches, createIndexRegex))
			{
				this->createIndex(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properCi;
				return 1;
			}
		}
		// Check for DROP TABLE command
		else if (regex_search(this->fullCmd, dt))
		{
			if (regex_search(this->fullCmd, matches, dropTableRegex))
			{
				this->dropTable(matches, tableList);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properDt;
				;
				return 1;
			}
		}
		// Check for DROP INDEX command
		else if (regex_search(this->fullCmd, di))
		{
			if (regex_search(this->fullCmd, matches, dropIndexRegex))
			{
				this->dropIndex(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properDi;
				return 1;
			}
		}
		// Check for DISPLAY TABLE command
		else if (regex_search(this->fullCmd, dplt))
		{
			if (regex_search(this->fullCmd, matches, displayTableRegex))
			{
				this->displayTable(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properDplt;
				return 1;
			}
		}
		// Check for INSERT INTO command
		else if (regex_search(this->fullCmd, ii))
		{
			if (regex_search(this->fullCmd, matches, insertIntoRegex))
			{
				this->insertInto(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properIi;
				return 1;
			}
		}
		// Check for DELETE FROM command
		else if (regex_search(this->fullCmd, df))
		{
			if (regex_search(this->fullCmd, matches, deleteFromRegex))
			{
				this->deleteFrom(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properDf;
				return 1;
			}
		}
		// Check for SELECT command
		else if (regex_search(this->fullCmd, st))
		{
			if (regex_search(this->fullCmd, matches, selectRegex))
			{
				this->select(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properSt;
				return 1;
			}
		}
		// Check for UPDATE command
		else if (regex_search(this->fullCmd, ue))
		{
			if (regex_search(this->fullCmd, matches, updateRegex))
			{
				this->update(matches);
				return 1;
			}
			else
			{
				cout << endl
						 << "Proper format is:"
						 << "\n"
						 << formats.properUe;
				return 1;
			}
		}

		return 0;
	}
	void
	setFullCmd()
	{
		// Set the full command by taking input from the user
		getline(cin, this->fullCmd);

		// Check if the length of the command is not empty
		if (this->fullCmd.length() <= 0)
		{
			this->fullCmd = "";

			// Throw an exception if there was an error reading the input
			throw runtime_error("Error reading the input. Try again.");
		}
	}

	// Method to retrieve the full command
	string getFullCmd()
	{
		return this->fullCmd;
	}

private:
	// Method for creating a table
	Table *createTable(smatch matches)
	{
		// Define a regex for partitioning the matches
		regex partitionRegex("[^() ,][a-zA-Z0-9]*");
		smatch partitionMatches;

		// Perform actions based on whether IF NOT EXISTS was used or not
		if (matches[2] == "")
		{
			// Perform an action if IF NOT EXISTS was not used
		}
		else
		{
			cout << endl
					 << "IF NOT EXISTS USED.";
		}

		// Extract the table name and content before partition from matches
		string tableName = matches[1].str();
		string beforePartition = matches[3].str();

		// Define regex iterators for partitioning
		auto words_begin =
				std::sregex_iterator(beforePartition.begin(), beforePartition.end(), partitionRegex);
		auto words_end = std::sregex_iterator();

		// Calculate the number of columns based on the distance between words_begin and words_end
		int noColumns = distance(words_begin, words_end) / 4;
		Column *columns = new Column[noColumns];

		int j = 0;
		int k = 0;

		// Iterate over the words and perform actions based on the current case
		for (std::sregex_iterator i = words_begin; i != words_end; ++i)
		{
			std::smatch match = *i;
			std::string match_str = match.str();

			switch (k)
			{
			case 0:
				columns[j].setColumnName(match_str);
				break;
			case 1:
				// Set the type of the column based on the match string
				if (toLowerCase(match_str) == "number")
					columns[j].setType(columnTypes::NUMBER);
				else if (toLowerCase(match_str) == "string")
					columns[j].setType(columnTypes::STRING);
				else
					throw runtime_error("Type of column must be number or string.");
				break;
			case 2:
				// Set the size of the column based on the match string converted to an integer
				columns[j].setSize(stoi(match_str));
				break;
			case 3:
				// Set the default value of the column based on the match string
				columns[j].setDefaultValue(match_str);
				break;
			}

			// Increment k and reset it to 0 if it reaches 4, increment j when k reaches 4
			k += 1;
			if (k == 4)
			{
				j += 1;
				k = 0;
			}
		}

		// Create and store the table
		Table *returnTable = new Table(tableName, columns, j);
		cout << *returnTable;

		// Store the table name in the tableList vector
		tableList.push_back(tableName);
		cout << tableList[0];
		return returnTable;
	}
	// trebuie lucrat de aici in jos

	// Method for dropping a table
	void dropTable(smatch matches, std::vector<std::string> &tableList)
	{
		// Check if the number of matches is less than 2
		if (matches.size() < 2)
		{
			std::cout << "Invalid input for dropping a table." << std::endl;
			return;
		}

		// Extract the table name from matches
		std::string tableName = matches[1].str();

		// Check if the table name has spaces
		int matchCount = std::count(matches.str().begin(), matches.str().end(), ' ');
		if (matchCount > 1)
		{
			std::cout << "Wrong command: too many table names." << std::endl;
			return;
		}

		// Check if there are too many table names
		std::string remaining = matches.suffix().str();
		if (std::count(remaining.begin(), remaining.end(), ',') > 0)
		{
			std::cout << "Wrong command: too many table names." << std::endl;
			return;
		}

		// Print the table name to ensure it is correct
		std::cout << "Table Name: " << tableName << std::endl;

		// Check if the tableList vector is empty
		if (tableList.empty())
		{
			std::cout << "Table list is empty." << std::endl;
			return;
		}

		// Find the table name in the tableList vector and erase it if found
		auto it = std::find(tableList.begin(), tableList.end(), tableName);
		if (it != tableList.end())
		{
			tableList.erase(it);
			std::cout << "Table " << tableName << " has been dropped." << std::endl;
		}
		else
		{
			std::cout << "Table " << tableName << " not found." << std::endl;
		}
	}

	void createIndex(smatch matches)
	{
		// de discutat la ce se refera
		return;
	}

	void dropIndex(smatch matches)
	{
		// same
		return;
	}

	void displayTable(smatch matches)
	{
		// afisarea este facuta in create table
		return;
	}

	void insertInto(smatch matches)
	{
		//
		return;
	}

	void deleteFrom(smatch matches)
	{
		//
		return;
	}

	void select(smatch matches)
	{
		//
		return;
	}

	void update(smatch matches)
	{
		//
		return;
	}
};