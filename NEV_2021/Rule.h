#pragma once
#include "stdafx.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), // стартовый символ
		TS('$'), //дно стека      
		6,									  // количество правил
		Rule(
			NS('S'),
			GRB_ERROR_SERIES + 0,    // неверная структура программы
			5,
			Rule::Chain(2, TS('u'), TS('l')),
			Rule::Chain(3, TS('u'), TS('l'), NS('S')),
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(
			NS('N'),
			GRB_ERROR_SERIES + 1,    // конструкции в функциях
			14,
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('('), TS('i'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('('), TS('l'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(12, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(8, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),

			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('p'), TS('('), TS('i'), TS(')'), TS(';')),
			Rule::Chain(5, TS('p'), TS('('), TS('l'), TS(')'), TS(';')),
			Rule::Chain(11, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(8, TS('y'), TS('('), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(8, TS('y'), TS('('), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'),  NS('N'))
		),
		Rule(
			NS('E'),
			GRB_ERROR_SERIES + 2,    // ошибка в выражении
			12,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('b'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('a'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(3, TS('i'), TS('+'), TS('l')),
			Rule::Chain(3, TS('i'), TS('+'), TS('i')),
			Rule::Chain(3, TS('l'), TS('+'), TS('l')),
			Rule::Chain(3, TS('i'), TS('-'), TS('l')),
			Rule::Chain(3, TS('i'), TS('-'), TS('i')),
			Rule::Chain(3, TS('l'), TS('-'), TS('l'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'),
			GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('C'),
			GRB_ERROR_SERIES + 5,    // условие if
			4,
			Rule::Chain(3, TS('i'), TS('o'), TS('i')),
			Rule::Chain(3, TS('i'), TS('o'), TS('l')),
			Rule::Chain(3, TS('l'), TS('o'), TS('i')),
			Rule::Chain(3, TS('l'), TS('o'), TS('l'))
		)

	);
}