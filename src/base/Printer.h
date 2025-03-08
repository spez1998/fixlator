#pragma once

#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>

#include "hffix.hpp"

class Printer
{
public:
	std::vector<std::map<int, std::string>> msgsMaps;

public:
	Printer();
	~Printer();
	void HFFixToMaps(std::vector<hffix::message_reader> msgs);
};