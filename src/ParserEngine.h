#pragma once
#include "hffix.hpp"

class ParserEngine
{
public:
	char *rawBuf = nullptr;
	std::vector<const char *> msgLocs;
	const char *partialMsg = nullptr;

public:
	ParserEngine();
	~ParserEngine();
	int RawToMaps(std::istream &in_stream);
	int TextToHffixMsgs(const char *raw_input);
	int ClearStoredMsgs();
};