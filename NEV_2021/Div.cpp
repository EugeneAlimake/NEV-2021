#include "stdafx.h"

unsigned char** divideText(In::IN in)		// формирование массива строк, состоящего из лексем
{
	int size = in.size; //передается размер текста
	unsigned char* text = in.text; //передается исходный текст
	unsigned char** word = new unsigned char* [MAX_WORDS]; //выделение памяти для разделения лексем
	for (int i = 0; i < MAX_WORDS; i++)
		word[i] = new unsigned char[WORD_SIZE] {NULL};

	bool findSP,//пробел – допускается везде кромеидентификаторов и ключевых слов;
	//; (точка с запятой) – разделитель инструкций;
	//{} – программный блок;
	//() – параметры;
	//() – приоритетность операци
		findLit = false;//числа
	//флаги сепараторов и литералов
	int j = 0;

	for (int i = 0, k = 0; i < size - 1; i++, k++) //проход текста
	{
		if (text[i] == '[') {
			for (i++; text[i] != ']';)
				i++;
			i++;
		}
		findSP = false;
		if (text[i] == '\"') //если найден литерал
			findLit = !findLit;

		if (((in.code[(unsigned char)text[i]] == In::IN::S) || (text[i] == DIV)) && !findLit) //проверка на сепаратор
		{
			findSP = true;
			if (word[j][0] != NULL)
			{
				word[j++][k] = IN_CODE_ENDL; //признак завершенности слова
				k = 0;
			}
			if (text[i] == ' ') //если пробел - пропускаем
			{
				k = -1;
				continue;
			}

			word[j][k++] = text[i]; //запись сепаратора
			if (text[i + 1] == LEX_EQUAL)
			{
				word[j][k++] = text[++i];	// запись логических операторов
			}

			word[j++][k] = IN_CODE_ENDL; //признак завершения разбора лексемы
			k = -1;
		}
		//}
		if (!findSP)		//если не сепаратор
			word[j][k] = text[i];		//переписывем
	}
	word[j] = NULL;
	//for (int i = 0; i < j; i++) //проверка
	//{
	//	if (!strcmp((char*)word[i], ""))
	//		return NULL;
	//	std::cout << i << ">"<< word[i] << " ";
	//}
	return word;
}
