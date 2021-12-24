#pragma once
#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_THROW_IN(id,l,c) Error::geterrorin(id,l,c);
#define ERROR_ENTRY(id, m) {id,m,{-1,-1}}        //Элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200                //максимальная длина сообщения об ошибке
#define ERROR_ENTRY_NODEF(id)	ERROR_ENTRY(-id,"Неопределенная ошибка") // 1 неопределенный элемент таблицы ошибок

// ERROR_ENTRY_NODEF5(id) - 5 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF5(id)	ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3),\
								ERROR_ENTRY_NODEF(id+4)

// ERROR_ENTRY_NODEF10(id) - 10 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF10(id) ERROR_ENTRY_NODEF5(id+0), ERROR_ENTRY_NODEF5(id+5)

// ERROR_ENTRY_NODEF50(id) - 50 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF50(id) ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
								ERROR_ENTRY_NODEF10(id+40)

// ERROR_ENTRY_NODEF10(id) - 100 неопределенных элементов таблицы ошибок
#define ERROR_ENTRY_NODEF100(id) ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
								ERROR_ENTRY_NODEF10(id+40),ERROR_ENTRY_NODEF10(id+50),ERROR_ENTRY_NODEF10(id+60),ERROR_ENTRY_NODEF10(id+70),\
								ERROR_ENTRY_NODEF10(id+80),ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 1000       //количество элементов в таблице ошибок

namespace Error
{
	struct ERROR      //тип исключения
	{
		int id;         //код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];    //сообщение об ошибке
		struct IN           // расширение для ошибок при обработке входных данных
		{
			short line;      //Номер строки
			short col;		//номер позиции в сроке
		}inext;
	};

	ERROR geterror(int id);       // сформирование ERROR для ERROR_THROW
	ERROR geterrorin(int id, int line, int col);// сформирование ERROR для ERROR_THROW_IN
};