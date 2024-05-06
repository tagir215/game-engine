#pragma once

struct ShaderComponent{
	int shaderId;
	ShaderComponent() : shaderId(-1) {}
	ShaderComponent(int id) : shaderId(id) {}
};