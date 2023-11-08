#pragma once
#include <iostream>
#include <string>
#include "utils.h"
#include "column_class.h"
#include "row_class.h"

using namespace std;

class Table
{
private:
	string name = " ";
	Column *columns = nullptr;
	int noColumns = 0;
	Row *rows = nullptr;
	int noRows = 0;

public:
	// pt tableBuffer
	// in viitor nu va mai fi public si prin inheritance il vom putea folosi doar in tableBuffer
	Table()
	{
	}

	Table(string inputName, Column *inputColumns, int inputNoColumns)
	{
		this->columns = new Column[inputNoColumns];

		this->setNoColumns(inputNoColumns);
		for (int i = 0; i < this->noColumns; i++)
		{
			this->columns[i] = inputColumns[i];
		}

		this->setName(inputName);
	}

	void insertOneRow(Row input)
	{
	}

	void insertRows(Row *input)
	{
	}

	string getName()
	{
		return this->name;
	}

	int getNoColumns()
	{
		return this->noColumns;
	}

	void setName(string input)
	{
		// validare: daca exista un table cu acelasi dam throw
		this->name = input;
	}

	void setNoColumns(int input)
	{
		this->noColumns = input;
	}

	Column *getColumns()
	{
		Column *newColumns = new Column[this->noColumns];

		for (int i = 0; i < this->noColumns; i++)
		{
			newColumns[i] = this->columns[i];
		}

		return newColumns;
	}

	void operator=(const Table &table)
	{
		this->name = table.name;

		Column *newCols = new Column[table.noColumns];
		for (int i = 0; i < table.noColumns; i++)
		{
			newCols[i] = table.columns[i];
		}
		this->columns = newCols;

		this->noColumns = table.noColumns;
	}

	Table(Table &table)
	{
		this->name = table.name;

		Column *newCols = new Column[table.noColumns];
		for (int i = 0; i < table.noColumns; i++)
		{
			newCols[i] = table.columns[i];
		}
		this->columns = newCols;

		this->noColumns = table.noColumns;
	}

	~Table()
	{
		delete[] this->columns;
	}
};

void operator<<(ostream &console, Table t)
{
	console << endl
					<< "~~~~ " << t.getName() << " ~~~~";
	console << endl
					<< "~~ No. of cols: " << t.getNoColumns();
	console << endl
					<< "~~~~~~~~~~~~~~~~";
	Column *columns = t.getColumns();
	for (int i = 0; i < t.getNoColumns(); i++)
	{
		console << columns[i];
	}
	delete[] columns;
}

class TableBuffer
{
	Table *tables = nullptr;
	int noTables = 0;

public:
	TableBuffer()
	{
	}

	Table *getTables()
	{
		Table *newTables = new Table[this->noTables];
		for (int i = 0; i < this->noTables; i++)
		{
			newTables[i] = this->tables[i];
		}
		return newTables;
	}

	int getNoTables()
	{
		return this->noTables;
	}

	void setNoTables(int input)
	{
		if (input < 0)
		{
			throw runtime_error("Number of tables must be positive or 0.");
		}
		this->noTables = input;
	}

	TableBuffer(const TableBuffer &tableBuffer)
	{
		this->noTables = tableBuffer.noTables;
		this->tables = new Table[tableBuffer.noTables];
		for (int i = 0; i < tableBuffer.noTables; i++)
		{
			this->tables[i] = tableBuffer.tables[i]; // Make a deep copy of each table
		}
	}

	void insertTable(const Table &input)
	{
		Table *newTables = new Table[this->noTables + 1];

		for (int i = 0; i < this->noTables; i++)
		{
			newTables[i] = this->tables[i];
		}

		newTables[this->noTables] = input;

		this->noTables += 1;

		delete[] this->tables;

		this->tables = newTables;
	}

	TableBuffer operator+(const Table &right)
	{

		TableBuffer copy = *this;
		copy.insertTable(right);

		return copy;
	}

	void operator=(const TableBuffer &right)
	{
		if (this == &right)
		{
			return;
		}
		delete[] this->tables;
		this->tables = new Table[right.noTables];
		for (int i = 0; i < right.noTables; i++)
		{
			this->tables[i] = right.tables[i];
		}
		this->noTables = right.noTables;
	}

	// daca nu l las asa si pun
	// delete[] tables;
	// imi sterge toate coloanele si toate tabelele
	~TableBuffer()
	{
	}
};