#pragma once

#include "model.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class ObjParser
{
public:
	static Model* Parse(const char* filepath);

private:
	ObjParser() {}
	~ObjParser() {}
};

