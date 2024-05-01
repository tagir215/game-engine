#pragma once
#include "shader.h"

struct ShaderInfo{
	int shaderId;
	ShaderInfo() : shaderId(-1) {}
	ShaderInfo(int id) : shaderId(id) {}
};