#include "stdafx.h"
namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM Input = { NULL, NULL, NULL, true }; //создание экземпл€ра структуры дл€ хранени€ информации

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE) //если длина параметра больше максимальной
			{
				throw ERROR_THROW(104)
			}
			if (wcsstr(argv[i], PARM_IN)) // wcsstr(arcg, PARM_IN) провер€ет на наличие строки  PARM_IN в строке arcg возвращает NULL если строку не находит
				wcscpy_s(Input.in, argv[i] + wcslen(PARM_IN));  // опируем в Input.in , путь к нашему файлу (содержимое argv , начина€ с wcslen(PARM_IN)( длины строки PARM_IN))
			else if (wcsstr(argv[i], PARM_OUT))
				wcscpy_s(Input.out, argv[i] + wcslen(PARM_OUT));// опируем в Input.out , путь к нашему файлу (содержимое argv , начина€ с wcslen(PARM_OUT)( длины строки PARM_OUT))
			else if (wcsstr(argv[i], PARM_LOG))
				wcscpy_s(Input.log, argv[i] + wcslen(PARM_LOG));// опируем в Input.log , путь к нашему файлу (содержимое argv , начина€ с wcslen(PARM_LOG)( длины строки PARM_LOG))
		}
		if (wcslen(Input.in) == 0) //если параметр -in: не задан
			throw ERROR_THROW(100);
		if (wcslen(Input.out) == 0)
		{
			wcscpy_s(Input.out, Input.in);//копирование в строку Input.out строки Input.in
			wcsncat_s(Input.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT)); // добавление wcslen(PARM_OUT_DEFAULT_EXT) символов строки PARM_OUT_DEFAULT_EXT в Input.out
		}
		if (wcslen(Input.log) == 0)
		{
			wcscpy_s(Input.log, Input.in);//копирование в строку Input.log строки Input.in
			wcsncat_s(Input.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT)); // добавление wcslen(PARM_OUT_DEFAULT_EXT) символов строки PARM_OUT_DEFAULT_EXT в Input.out
		}
		return Input;
	}
}