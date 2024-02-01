#pragma once
#include "../shader/shader.h"

struct ShaderInfo{
	int shaderId;
	ShaderInfo() : shaderId(0) {}
	ShaderInfo(int id) : shaderId(id) {}
};