#pragma once
#include "stdafx.h"

#define MAX_USHORT 65535

namespace Lex
{
	bool checkBrace(unsigned char** word, int k);
	struct LEX
	{
		IT::IdTable idTable;;
		LT::LexTable lexTable;
	};

	LEX lexAnaliz(Log::LOG log, In::IN in);
}