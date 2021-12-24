#pragma once
#include "stdafx.h"

#define PARAMS_MAX 8 //максимальное количество символов в именовании 

namespace Sem
{
	bool checkSemantic(Lex::LEX& lex, Log::LOG& log);
};