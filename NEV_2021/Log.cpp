#include "stdafx.h"
namespace Log
{

	LOG getlog(wchar_t logfile[]) //Используется для создания и открытия потокового вывода протокола.
	//открывает (создает) выходной поток;
	{
		LOG temp;
		temp.stream = new std::ofstream(logfile);					//динамическое выделение ofstream и инициализация указателя на этот объект и открытие
		if (!temp.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(temp.logfile, logfile);							//копирование logfile в temp.logfile
		return temp;
	}

	void WriteLine(LOG log, const char* c, ...)//осуществляет конкатенацию всех строк заданных параметрами, 
	{
		const char** ptr = &c;										//берем адрес-адреса
		while (strlen(*ptr))										//пока не встретим L""
		{
			*log.stream << *ptr;									// запись в файл параметра
			++ptr;													//перемещаемся на следующий параметр
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)//формирует строку и выводит ее в протокол.
	
	{
		const wchar_t** ptr = &c;
		while (wcslen(*ptr))		//wcslen () возвращает длину заданной широкой строки
		{
			char out[PARM_MAX_SIZE];
			size_t charsConverted = 0;								//функция преобразовавающая wchar_t* в char
			wcstombs_s(&charsConverted, out, *ptr, PARM_MAX_SIZE);	//Преобразует последовательность расширенных символов в соответствующую 
			//последовательность многобайтовых символов
			// 1-ый аргумент: Размер в байтах преобразованной строки, включая нулевой терминатор 2-
			*log.stream << out;										// запись в файл параметра	
			++ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLog(LOG log) //Используется для вывода заголовка протокола вреиени
	//для получения текущей даты и времени в формате строки используйте функции time, localtime_s и strftime.
	{
		time_t  t = time(nullptr);									// time_t = количество секунд time()- Текущее календарное время типа c 1 января 1970 
		tm  now;														// структура содержащая сек мин час ...
		localtime_s(&now, &t);										//Преобразует time_t в календарное время, выраженное в местном времени в хранилище struct tm
		char date[PARM_MAX_SIZE];									//массив для вывода времени
		strftime(date, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);	//фукнция преобразующая структуру tm в массив c макс кол-вом символов для копирования PARM_MAX_SIZE в формате day month year...
		*log.stream << "---- Протокол ------- \n Дата: " << date << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)//Используется для вывода в протокол информации о входных параметрах
		//выводит в протокол информацию о параметрах(образец в тесте)
	{
		*log.stream << "---- Параметры -------" << std::endl;
		char out[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, out, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << out << std::endl;
	}

	void WriteIn(LOG log, In::IN in)//Используется для вывода в протокол информации о входных данных(исходный код)
	//выводит в протокол информацию о входных данных(образец в тесте)
	{
		*log.stream << "---- Исходные данные -----" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано:     " << in.ignor << std::endl;
		*log.stream << "Количество строк:    " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)//Используется для вывода в протокол или на консоль информации об ошибке.
	// выводит в протокол информацию об ошибке; если протокол не открыт, выводит информацию на консоль(образец в тесте)
	{
		if (log.stream == nullptr || !log.stream->is_open())
		{
			std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		}
		else
		{
			*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		}
	}

	void Close(LOG log)//Используется для закрытия выходного потока протокола.
	{
		if (log.stream != nullptr)									//если поток открыт
		{
			log.stream->close();
			delete log.stream;
		}
	}

}