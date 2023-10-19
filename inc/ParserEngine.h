#pragma once
#include "hffix.hpp"

class ParserEngine
{
public:
	char *rawBuf;
	std::vector<const char *> msgLocs;
	const char *partialMsg;

public:
	ParserEngine();
	int RawToMaps(std::istream &in_stream);
	int TextToHffixMsgs(const char *raw_input);
};