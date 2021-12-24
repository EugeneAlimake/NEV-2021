#pragma once
#define LEXEMA_FIXSIZE	1			// фиксированный размер лексемы
#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов
#define LEX_USELIB		'u'	// лексема для uselib
#define LEX_USHORT		't'	// лексема для integer
#define LEX_STRING		't'	// лексема для string
#define LEX_ID			'i'	// лексема для идентификатора
#define LEX_LITERAL		'l'	// лексема для литерала
#define LEX_FUNCTION	'f'	// лексема для function
#define LEX_VAR			'd'	// лексема для var
#define LEX_RETURN		'r'	// лексема для return
#define LEX_PRINT		'p'	// лексема для print
#define LEX_IF			'c'	// лексема для if
#define LEX_ELSE		'e'	// лексема для else
#define LEX_LOGICAL		'o'	// лексема для логических операторов
#define LEX_MAIN		'm'	// лексема для main
#define LEX_POW			'b'	// лексема для pow
#define LEX_COMPARE		'a'	// лексема для compare
#define LEX_SEMICOLON	';'	// лексема для ;
#define LEX_COMMA		','	// лексема для ,
#define LEX_LEFTBRACE	'{'	// лексема для {
#define LEX_RIGHTBRACE	'}'	// лексема для }
#define LEX_LEFTTHESIS	'('	// лексема для (
#define LEX_RIGHTTHESIS	')'	// лексема для )
#define LEX_EQUAL		'='
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_CYCLE		'y'	// цикл

namespace LT		// таблица лексем
{
	struct Entry	// строка таблицы лексем
	{
		unsigned char lexema;	// лексема
		int numOfString;				// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
		int priority;					// приоритет
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxSize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < maxSize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(		// создать таблицу лексем
		int size			// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(				// добавить строку в таблицу лексем
		LexTable& lexTable,	// экземпляр таблицы лексем
		Entry entry			// строка таблицы лексем
	);

	Entry GetEntry(			// получить строку таблицы лексем
		LexTable& lexTable,	// экземпляр таблицы лексем
		int n				// номер получаемой строки
	);

	void Delete(LexTable& lexTable);	// удалить таблицу лексем (освободить память)

	Entry writeEntry(					// заполнить строку таблицы лексем
		Entry& entry,
		unsigned char lexema,
		int indx,
		int line
	);

	void showTable(LexTable lexTable, Log::LOG& log);	// вывод таблицы лексем
	void show(LexTable lexTable, Parm::PARM parm);
};