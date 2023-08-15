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

class HffixMsg
{
public:
	void* buf;
	hffix::message_reader msg;
	HffixMsg();
	/*
		Looks like I'll have to split up / malloc chunks of my input buffer to instances of this
		class, which have associated with them a message_reader
	*/
};

class ParserEngine
{
private:
	enum {chunksize = 4096}; // Choose a preferred I/O chunk size.
	char buffer[1 << 20]; // Must be larger than the largest FIX message size.

public:
	// Vector of <tuple<int,string>, string> maps.
	// Tuple for tags' numbers and names (if name string exists), cast any value to a string.
	std::vector< std::map< std::tuple<int,std::string> , std::string>> messages;

	// Isn't it worth just using the nice data structure provided to us?
	std::vector<hffix::message_reader> messages_hffix;

public:
	ParserEngine();
	~ParserEngine();
	int RawToMaps(std::istream& in_stream);
	int TextToHffixMsgs(std::istream& in_stream);
};