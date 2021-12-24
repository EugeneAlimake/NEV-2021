#include "stdafx.h"
namespace Error
{
	/*Серии ошибок   0-99		 системные ошибки САНЯ
					 100-109	 ошибки параметров
					 110-119	 ошибки открытия и чтения файлов
	*/
	ERROR errors[ERROR_MAX_ENTRY] =  //таблица ошибок
	{
		ERROR_ENTRY(0,"[Системная] Недопустимый код ошибки"), //код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"[Системная] Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF5(5),ERROR_ENTRY_NODEF50(10), ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"[Системная] Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"[Системная] Превышена длинна входного параматра"),
		ERROR_ENTRY_NODEF5(105),
		ERROR_ENTRY(110,"[Системная] Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"[Системная] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"[Системная] Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"[Системная] Ошибка при открытии выходного файла (-out)"),
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF5(115),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200,"[Лексическая] Двойное объявление"),
		ERROR_ENTRY(201,"[Лексическая] Ошибка лексического анализа"),
		ERROR_ENTRY(202,"[Лексическая] Длина идентификатора больше 8"),
		ERROR_ENTRY(203,"[Лексическая] Идентификатор не определён"),
		ERROR_ENTRY(204,"[Лексическая] Ошибка, максимальный размер таблицы идентификаторов 4096"),
		ERROR_ENTRY(205,"[Лексическая] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(206,"[Лексическая] Ошибка, максимальный размер таблицы лексем 4096"),
		ERROR_ENTRY(207,"[Лексическая] Таблица лексем переполнена"),
		ERROR_ENTRY(208,"[Лексическая] Максимальное значение типа ushort 65535"),
		ERROR_ENTRY_NODEF(209), ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220),
		ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF50(250), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY(500,"[Cемантическая] Нет точки входа main"),
		ERROR_ENTRY(501,"[Cемантическая] Более одной точки входа main"),
		ERROR_ENTRY(502,"[Cемантическая] Возвращаемое значение не соответствует типу функции"),
		ERROR_ENTRY(503,"[Cемантическая] Количество параметров функции больше допустимого"),
		ERROR_ENTRY(504,"[Cемантическая] Передаваемые параметры не соответствуют функции"),
		ERROR_ENTRY(505,"[Cемантическая] Не соответсвует количество передаваемых параметров"),
		ERROR_ENTRY(506,"[Cемантическая] Ошибка в параметрах функции pow()"),
		ERROR_ENTRY(507,"[Cемантическая] Ошибка в параметрах функции compare()"),
		ERROR_ENTRY(508,"[Cемантическая] Попытка сравнения операндов не типа ushort"),
		ERROR_ENTRY(509,"[Cемантическая] Ошибка в параметре функции print()"),
		ERROR_ENTRY(510,"[Cемантическая] Ошибка в подключении библиотеки"),
		ERROR_ENTRY(511,"[Cемантическая] Ошибка в парасетрах цикла cycle()"),
		ERROR_ENTRY_NODEF(512),ERROR_ENTRY_NODEF(513),ERROR_ENTRY_NODEF(514
		), ERROR_ENTRY_NODEF5(515), ERROR_ENTRY_NODEF10(520),
		ERROR_ENTRY_NODEF10(530), ERROR_ENTRY_NODEF10(540), ERROR_ENTRY_NODEF50(550),
		ERROR_ENTRY(600,"[Cинтаксическая] Неверная структура программы"),
		ERROR_ENTRY(601,"[Cинтаксическая] Ошибочная конструкция в функции"),
		ERROR_ENTRY(602,"[Cинтаксическая] Ошибка в выражении"),
		ERROR_ENTRY(603,"[Cинтаксическая] Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"[Cинтаксическая] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605,"[Cинтаксическая] Ошибка в условии"),
		ERROR_ENTRY(606,"[Cинтаксическая] Ошибка в операторе"),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF50(650), ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR error_info;											// создание структуры которую надо будет вернуть
		if (id > 0 && id < ERROR_MAX_ENTRY)							// сравнивание диапазона
		{
			error_info.id = errors[id].id;
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			error_info.id = errors[0].id;
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	создание структуру которую надо будет вернуть
		if (id > 0 && id < ERROR_MAX_ENTRY)						// сравнение диапазона
		{
			error_info.id = errors[id].id;
			error_info.inext.col = col;
			error_info.inext.line = line;
			strcpy_s(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0; // заношу
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy_s(error_info.message, errors[0].message);
			return error_info;
		}
	}
	;
};