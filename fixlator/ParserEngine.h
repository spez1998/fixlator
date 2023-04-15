#pragma once

#include "hffix.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

class ParserEngine
{
private:
	enum { chunksize = 4096 }; // Choose a preferred I/O chunk size.
	char buffer[1 << 20]; // Must be larger than the largest FIX message size.

private:
	void testEngine(std::istream& stream);
};
