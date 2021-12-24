#include "stdafx.h"

int _tmain(int argc, _TCHAR ** argv)
{
	setlocale(LC_ALL, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv); //передача и обработка параметров
		log = Log::getlog(parm.log);//Используется для создания и открытия потокового вывода протокола
		Log::WriteLine(log, L"Тест", L" Без ошибок", L"");////формирует строку и выводит ее в протокол.
		Log::WriteLog(log);////Используется для вывода заголовка протокола вреиени
		Log::WriteParm(log, parm);//выводит в протокол информацию о параметрах(образец в тесте)
		In::IN in = In::getin(parm.in);//чтение файла
		Log::WriteIn(log, in);// данные из in файла
		Lex::LEX lex = Lex::lexAnaliz(log, in); //соответственно производит лексический анализ
		//Последовательное
		//выходом лексического анализатора является таблица лексем (ТЛ) и таблица идентификаторов (ТИ)
		LT::show(lex.lexTable, parm);
		IT::show(lex.idTable, parm);
		std::cout << "Лексический анализ завершён без ошибок\n\n";
		*log.stream << "\nЛексический анализ завершён без ошибок\n\n";
		LT::showTable(lex.lexTable, log);
		IT::showTable(lex.idTable, log);
		
		/*MFST_TRACE_START*/
		MFST::Mfst mfst(lex, GRB::getGreibach(), parm.trace);
		mfst.start();											// старт синтаксического анализа
		mfst.savededucation();
		if (!mfst.start())
			throw ERROR_THROW(600);
		std::cout << "Синтаксический анализ завершён без ошибок\n";
		*log.stream << "Синтаксический анализ завершён без ошибок\n\n";
		mfst.printrules();

		if (Sem::checkSemantic(lex, log))
		{
			std::cout << "\nСемантический анализ завершён без ошибок\n\n";
			*log.stream << "Семантический анализ завершён без ошибок\n\n";
		}
		Gen::CodeGeneration(lex, parm.out);
	

		system("pause");
		Log::Close(log);
	}
	catch (Error::ERROR error)
	{
		Log::WriteError(log, error);
		std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		system("pause");
	}
	return 0;
}