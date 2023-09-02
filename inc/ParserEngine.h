#pragma once

#include "hffix.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
#include <tuple>
#include <format>

struct HffixMsg
{
	char* buf;
	size_t size;
	HffixMsg(size_t size);
};

class ParserEngine
{
private:
	enum {chunksize = 4096}; // Choose a preferred I/O chunk size.
	char buffer[1 << 20]; // Must be larger than the largest FIX message size.

public:
	std::vector<HffixMsg> messages_hffix;

public:
	ParserEngine();
	int RawToMaps(std::istream& in_stream);
	int TextToHffixMsgs(std::istream& in_stream);
};