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

class ParserEngine
{
private:
	enum {chunksize = 4096}; // Choose a preferred I/O chunk size.
	char buffer[1 << 20]; // Must be larger than the largest FIX message size.

public:
	// Vector of <tuple<int,string>, string> maps.
	// Tuple for tags' numbers and names (if name string exists), cast any value to a string.
	std::vector< std::map< std::tuple<int,std::string> , std::string>> messages;

public:
	ParserEngine();
	~ParserEngine();
	int RawToMaps(std::istream& in_stream);
};