#include "stdafx.h"
#pragma warning(disable:4996)

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define SLASH '/'
#define EQUAL '='

using namespace std;

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE); //создание таблицы лексем макс размера
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);//создание таблицы индефикаторов макс размера

		unsigned char** word = new unsigned char* [MAX_WORDS]; //выделение памяти для разделения лексем
		for (int i = 0; i < MAX_WORDS; i++)
			word[i] = new unsigned char[WORD_SIZE] {NULL};

		word = divideText(in); //разделение на лексемы 


		int indexLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int countLit = 1;		// счетчик литералов
		int line = 1;			// номер строки
		int enterCount = 0;		// кол-во main

		unsigned char emptystr[] = "";	// пустая строка
		unsigned char* regionPrefix = new unsigned char[10]{ "" };	// текущий префикс
		unsigned char* bufRegionPrefix = new unsigned char[10]{ "" };	// буфер для префикса
		unsigned char* oldRegionPrefix = new unsigned char[10]{ "" };	// предыдущий префикс
		unsigned char* L = new unsigned char[2]{ "L" };		// начальный символ для имён литералов + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE] { "" };
		char* charCountLit = new char[10]{ "" };		// для строковой записи счетчика
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //для области видимости

		bool findFunc = false;
		bool findParm = false;
		bool findDeclaration = false;
		IT::Entry entryIT; //создание лексемы для занесения в табл идентификаторов 

		for (int i = 0; word[i] != NULL; i++, indexLex++) //проход по всем лексемам
		{

			bool findSameID = false;

			FST::FST fstLib(word[i], FST_USELIB); // проверка на ключевое слово
			if (FST::execute(fstLib))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_USELIB, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				continue;
			}

			FST::FST fstIf(word[i], FST_IF); // проверка на ключевое слово
			if (FST::execute(fstIf))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_IF, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				continue;
			}

			FST::FST fstElse(word[i], FST_ELSE); // проверка на ключевое слово
			if (FST::execute(fstElse))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				continue;
			}
			FST::FST fstCycle(word[i], FST_CYCLE);// проверка на ключевое слово
			if (FST::execute(fstCycle))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_CYCLE, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				continue;
			}

			FST::FST fstLogical(word[i], FST_LOGICAL); // проверка на ключевое слово
			if (FST::execute(fstLogical))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LOGICAL, indexID++, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				_mbscpy(entryIT.id, word[i]);

				entryIT.idxfirstLE = indexLex;
				entryIT.idType = IT::OP;
				IT::Add(idTable, entryIT);
				continue;
			}

			FST::FST fstDeclare(word[i], FST_DECLARE); // проверка на ключевое слово
			if (FST::execute(fstDeclare))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_VAR, LT_TI_NULLIDX, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				continue;
			}
			FST::FST fstTypeInteger(word[i], FST_INTEGER);// проверка на ключевое слово
			if (FST::execute(fstTypeInteger))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_USHORT, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idDataType = IT::USHORT; //запись типа идентификатора в структуру
				findDeclaration = true;
				continue;
			}
			FST::FST fstTypeString(word[i], FST_STRING);// проверка на ключевое слово
			if (FST::execute(fstTypeString))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_STRING, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idDataType = IT::STR;			//запись типа идентификатора в структуру
				_mbscpy(entryIT.value.vstr.str, emptystr); //очистка строки для записи идентификатора
				findDeclaration = true;
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNCTION);// проверка на ключевое слово
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);

				entryIT.idType = IT::F;
				findFunc = true; //установка флага функции
				continue;
			}
			FST::FST fstReturn(word[i], FST_RETURN);// проверка на ключевое слово
			if (FST::execute(fstReturn))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RETURN, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstPrint(word[i], FST_PRINT);// проверка на ключевое слово
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PRINT, indexID++, line);
				LT::Add(lexTable, entryLT);
				entryIT.idType = IT::LIB;
				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}
			FST::FST fstMain(word[i], FST_MAIN);// проверка на ключевое слово
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_MAIN, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				enterCount++;
				_mbscpy(oldRegionPrefix, regionPrefix);
				_mbscpy(regionPrefix, word[i]);
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID); //проверка на идентификатор
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibPow(word[i], FST_LIB_POW); //проверка
				FST::FST fstLibCompare(word[i], FST_LIB_COMPARE); //проверка

				if (_mbslen(word[i]) > ID_MAXSIZE)
					throw ERROR_THROW_IN(202, line, 0);
				_mbscpy(startWord, word[i]);

				// поиск такого же
				if (findFunc)	// если функция
				{
					int idx = IT::IsIDRegion(idTable, word[i]);	// ищем без префикса
					if (idx != TI_NULLIDX)						// если такой идентификатор уже есть
					{
						if (lexTable.table[indexLex - 1].lexema == LEX_FUNCTION)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idTable, word[i]);
					if (idx != TI_NULLIDX)
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
					_mbscpy(bufRegionPrefix, regionPrefix);
					word[i] = _mbscat(bufRegionPrefix, word[i]);
					idx = IT::IsIDRegion(idTable, word[i]);
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);
				if (findParm)				// если параметр
				{
					entryIT.idType = IT::P;
				}
				else if (!findFunc)
				{
					// если переменная
					if (findDeclaration)
					{
						entryIT.idType = IT::V;
						if (entryIT.idDataType == IT::USHORT)
							entryIT.value.vushort = TI_INT_DEFAULT;
						if (entryIT.idDataType == IT::STR) {
							entryIT.value.vstr.len = 0;
							memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
						}
						findDeclaration = false;
					}
					else
					{
						FST::FST fstLibPow(startWord, FST_LIB_POW);
						FST::FST fstLibCompare(startWord, FST_LIB_COMPARE);
						if (FST::execute(fstLibPow))
						{
							entryLT.lexema = LEX_POW;
							entryIT.idType = IT::LIB;
						}
						else if (FST::execute(fstLibCompare))
						{
							entryLT.lexema = LEX_COMPARE;
							entryIT.idType = IT::LIB;
						}
						else
						{
							throw ERROR_THROW_IN(203, line, 0);
						}
					}
				}
				else {		// если функция
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				LT::Add(lexTable, entryLT);
				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				findFunc = false;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_INTLIT); //если литерал 
			FST::FST fstLiteralBin(word[i], FST_BINLIT);

			if (FST::execute(fstLiteralInt) || FST::execute(fstLiteralBin))
			{
				unsigned short value;
				char* buf;
				if (word[i][0] == '0')
				{
						value = strtoll((const char*)word[i], NULL, 8);
				}
					
				else
				{
					if (atoi((char*)word[i]) > MAX_USHORT)
						throw ERROR_THROW_IN(208, line, 0);
					value = strtoll((const char*)word[i], NULL, 2);
					/*value = atoi((char*)word[i]);	*/// значение литерала
				}	
				
				for (int k = 0; k < idTable.size; k++) // поиск такого же
				{
					if (idTable.table[k].value.vushort == value && idTable.table[k].idType == IT::L)
					{
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lexTable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
				{
					continue;
				}

				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::USHORT;
				entryIT.value.vushort = value;
				entryIT.idxfirstLE = indexLex;	//номер в табл лексем
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit) 

				// формирование имени литерала
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// запись значения
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];

				word[i][length - 2] = '\0';


				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// запись значиния строкового литерала
				entryIT.value.vstr.len = length - 2;		// запись длины строкового литерала
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::STR;
				entryIT.idxfirstLE = indexLex;
				// формирование имени литерала
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала (L + charCountLit)
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, nameLiteral);
				IT::Add(idTable, entryIT);
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lexTable, entryLT);
				if (indexID != 0)
					if (idTable.table[indexID - 1].idType == IT::F)
						findParm = true;
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;

				if (findParm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE && !checkBrace(word, i + 1))		// если после функции нет {
					_mbscpy(regionPrefix, oldRegionPrefix);		// возвращаем предыдущую обл. видимости
				findParm = false;
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstPlus(word[i], FST_PLUS);
			if (FST::execute(fstPlus))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PLUS, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}
			FST::FST fstMinus(word[i], FST_MINUS);
			if (FST::execute(fstMinus))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_MINUS, LT_TI_NULLIDX, line);
				LT::Add(lexTable, entryLT);
				continue;
			}

			if (word[i][0] == DIV) {
				line++;
				indexLex--;
				continue;
			}
			throw ERROR_THROW_IN(201, line, 0);
		}
		if (enterCount == 0)
		{
			throw ERROR_THROW_IN(500, 0, 0);
		}
		if (enterCount > 1)
		{
			throw ERROR_THROW_IN(501, 0, 0);
		}
		lex.idTable = idTable;
		lex.lexTable = lexTable;
		return lex;
	}

	bool checkBrace(unsigned char** word, int k)
	{
		while (word[k][0] == DIV)
		{
			k++;
		}
		if (word[k][0] == LEX_LEFTBRACE)
			return 1;
		else
			return 0;
	}
}