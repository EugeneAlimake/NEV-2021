#include "stdafx.h"
#include <queue>

namespace Sem
{
	bool Sem::checkSemantic(Lex::LEX& tables, Log::LOG& log)
	{
		for (int i = 0; i < tables.lexTable.size; i++)
		{
			switch (tables.lexTable.table[i].lexema)
			{
			case LEX_USELIB: // проверка uselib
			{
				if (tables.lexTable.table[++i].lexema == LEX_LITERAL)
					if (tables.idTable.table[tables.lexTable.table[i].idxTI].idDataType == IT::STR)
						break;
				throw ERROR_THROW_IN(510, tables.lexTable.table[i].numOfString, 0); //ошибка при подключении библиотееи
			}
			case LEX_PRINT: // проверка print
			{
				i++;
				if (tables.lexTable.table[i++].lexema == LEX_LEFTTHESIS)
					if (tables.lexTable.table[i].lexema == LEX_ID || tables.lexTable.table[i].lexema == LEX_LITERAL)
						break;
				throw ERROR_THROW_IN(509, tables.lexTable.table[i].numOfString, 0);
			}
			case LEX_LOGICAL: // проверка логический операторов
			{
				IT::IDDATATYPE dataTypeLeftOp = tables.idTable.table[tables.lexTable.table[i - 1].idxTI].idDataType;
				IT::IDDATATYPE dataTypeRightOp = tables.idTable.table[tables.lexTable.table[i + 1].idxTI].idDataType;

				if (dataTypeLeftOp != IT::USHORT || dataTypeRightOp != IT::USHORT)
					throw ERROR_THROW_IN(508, tables.lexTable.table[i].numOfString, 0);

				break;
			}
			case LEX_POW: // проверка pow 
			{
				int paramsCount = 0;

				for (int j = i + 2; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
				{
					if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
					{
						paramsCount++;
						IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].idxTI].idDataType;
						if (ctype != IT::USHORT)
							throw ERROR_THROW_IN(506, tables.lexTable.table[i].numOfString, 0);
					}
				}
				if (paramsCount != 2)
					throw ERROR_THROW_IN(506, tables.lexTable.table[i].numOfString, 0);
				break;
			}
			case LEX_COMPARE: // проверка compare
			{
				int paramsCount = 0;

				for (int j = i + 2; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
				{
					if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
					{
						paramsCount++;
						IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].idxTI].idDataType;
						if (ctype != IT::STR)
							throw ERROR_THROW_IN(507, tables.lexTable.table[i].numOfString, 0);
					}
				}
				if (paramsCount != 2)
					throw ERROR_THROW_IN(507, tables.lexTable.table[i].numOfString, 0);
				break;
			}
			case LEX_CYCLE:
			{
				int paramsCount = 0;
				for (int j = i + 2 ; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
				{
					if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
					{
						paramsCount++;
						IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].idxTI].idDataType;
						if (ctype != IT::USHORT)
							throw ERROR_THROW_IN(511, tables.lexTable.table[i].numOfString, 0);
					}
				}
				if (paramsCount != 1)
					throw ERROR_THROW_IN(511, tables.lexTable.table[i].numOfString, 0);
				break;

			}
			case LEX_ID:
			{
				IT::Entry tmp = tables.idTable.table[tables.lexTable.table[i].idxTI];

				if (i > 0 && tables.lexTable.table[i - 1].lexema == LEX_FUNCTION)
				{
					if (tmp.idType == IT::F)
					{
						for (int k = i + 1; k != tables.lexTable.size; k++)
						{
							char l = tables.lexTable.table[k].lexema;
							if (l == LEX_RETURN)
							{
								int lexAfterReturn = tables.lexTable.table[k + 1].idxTI; // след. за return
								if (lexAfterReturn != TI_NULLIDX)
								{
									// тип функции и возвращаемого значения не совпадают
									if (tables.idTable.table[lexAfterReturn].idDataType != tmp.idDataType)
									{
										throw ERROR_THROW_IN(502, tables.lexTable.table[k].numOfString, 0);
									}
								}
								break;
							}
						}
					}
				}
				if (tables.lexTable.table[i + 1].lexema == LEX_LEFTTHESIS && tables.lexTable.table[i - 1].lexema != LEX_FUNCTION) // вызов
				{
					if (tmp.idType == IT::F)
					{
						std::queue<LT::Entry> queue;

						int protoParamsCount = 0;

						for (int iterator = tmp.idxfirstLE + 1; tables.lexTable.table[iterator].lexema != LEX_RIGHTTHESIS; iterator++)
						{
							if (tables.lexTable.table[iterator].lexema == LEX_ID) {
								protoParamsCount++;
								queue.push(tables.lexTable.table[iterator]);
							}
						}
						if (protoParamsCount > PARAMS_MAX)
							throw ERROR_THROW_IN(503, tables.lexTable.table[i].numOfString, 0);

						// проверка передаваемых параметров
						for (int j = i + 1; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
						{
							// проверка соответствия передаваемых параметров прототипам
							if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
							{
								IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].idxTI].idDataType;
								if (!queue.empty())
								{
									if (ctype != tables.idTable.table[queue.front().idxTI].idDataType)
									{
										// Несовпадение типов передаваемых параметров
										throw ERROR_THROW_IN(504, tables.lexTable.table[i].numOfString, 0);
									}
									queue.pop();
								}
								else
								{
									// Количество передаваемых и принимаемых параметров не совпадает
									throw ERROR_THROW_IN(505, tables.lexTable.table[i].numOfString, 0);
								}
							}
						}
						if (!queue.empty())
						{
							throw ERROR_THROW_IN(505, tables.lexTable.table[i].numOfString, 0);
						}
					}
				}
				char prevLex = tables.lexTable.table[i - 1].lexema;
				if (tmp.idxfirstLE == i && prevLex != LEX_USHORT && prevLex != LEX_STRING && prevLex != LEX_FUNCTION)
					throw ERROR_THROW_IN(203, tables.lexTable.table[i].numOfString, 0);
				break;
			}

			}
		}
		return true;
	}
}