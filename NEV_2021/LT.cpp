#include "stdafx.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE) throw ERROR_THROW(206);
		LexTable Table;
		Table.maxSize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(LexTable& lexTable, Entry entry)
	{
		if (lexTable.size > lexTable.maxSize) throw ERROR_THROW(207);
		lexTable.table[lexTable.size++] = entry;
	}

	Entry GetEntry(LexTable& lexTable, int n)
	{
		return lexTable.table[n];
	}

	void Delete(LexTable& lexTable)
	{
		lexTable.maxSize = NULL;
		lexTable.size = NULL;
		delete[] lexTable.table;
	}

	Entry writeEntry(Entry& entry, unsigned char lexema, int indx, int line)
	{
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.numOfString = line;
		return entry;
	}

	void showTable(LexTable lexTable, Log::LOG& log)		// вывод таблицы лексем
	{
		int number = 1;
		*log.stream << "01 ";
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].numOfString != number && lexTable.table[i].numOfString != -1)
			{
				while (lexTable.table[i].numOfString - number > 1)	// пока строки не станут равны
					number++;
				if (number < 9)
					*log.stream << std::endl << '0' << lexTable.table[i].numOfString << ' ';
				else
					*log.stream << std::endl << lexTable.table[i].numOfString << ' ';
				number++;
			}
			*log.stream << lexTable.table[i].lexema;
			if (lexTable.table[i].lexema == LEX_ID || lexTable.table[i].lexema == LEX_LITERAL || lexTable.table[i].lexema == LEX_LOGICAL)
				*log.stream << "<" << lexTable.table[i].idxTI << ">";
		}
	}

	void show(LexTable lexTable, Parm::PARM parm)		// вывод таблицы лексем
	{
		int number = 1;
		cout << "01 ";
		for (int i = 0; i < lexTable.size; i++)
		{
			if (lexTable.table[i].numOfString != number && lexTable.table[i].numOfString != -1)
			{
				while (lexTable.table[i].numOfString - number > 1)	// пока строки не станут равны
					number++;
				if (number < 9)
					cout << std::endl << '0' << lexTable.table[i].numOfString << ' ';
				else
					cout << std::endl << lexTable.table[i].numOfString << ' ';
				number++;
			}
			cout << lexTable.table[i].lexema;
			if (lexTable.table[i].lexema == LEX_ID || lexTable.table[i].lexema == LEX_LITERAL || lexTable.table[i].lexema == LEX_LOGICAL)
				cout << "<" << lexTable.table[i].idxTI << ">";
		}
	}
}