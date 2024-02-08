#pragma once
#include "shader.h"

struct ShaderInfo{
	int shaderId;
	ShaderInfo() : shaderId(0) {}
	ShaderInfo(int id) : shaderId(id) {}
};