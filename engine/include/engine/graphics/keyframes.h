#pragma once
#include <vector>
#include <array>

class Keyframes {
public:
	Keyframes(int columns, int rows) : w(1.0f / static_cast<float>(columns)), h(1.0f / static_cast<float>(rows)){

	}
	std::vector<std::vector<float>>frames;
protected:
	const float w;
	const float h;
};