#pragma once

#include "model.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class ObjParser
{
public:
	static void Parse(const char* filepath, std::vector<Model*>& models);

private:
	ObjParser() {}
	~ObjParser() {}
};

