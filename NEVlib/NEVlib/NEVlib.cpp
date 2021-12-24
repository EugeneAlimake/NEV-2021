#include <cstdlib>
#include <iostream>
#include <string.h>

extern "C" {
	void _printN(unsigned short a)
	{
		std::cout << a << std::endl;
	}

	void _printS(char* str)
	{
		std::cout << str << std::endl;
	}

	unsigned short _pow(int num, int exponent)
	{
		unsigned short accum = 1;
		for (int i = 0; i < exponent; i++)
		{
			if (accum * num > 65535)
			{
				std::cout << "Overflow in pow()" << std::endl;
				throw - 1;
			}
			accum *= num;
		}
		return accum;
	}

	unsigned short _compare(char* a, char* b)
	{
		if (strcmp(a, b) < 0) 
		{
			std::cout << "strings are not equal" << std::endl;
			return 0;
		}
		if (strcmp(a, b) == 0)
		{
			std::cout << "strings are equal" << std::endl;
			return 1;
		}
		if (strcmp(a, b) > 0) 
		{
			std::cout << "strings are not equal" << std::endl;
			return 2;
		}
	}

	void _pause() {
		system("pause");
	}
}