#pragma once
#include <vector>
#include <array>

class Keyframes {
public:
	Keyframes(int columns, int rows) : w(1.0f / static_cast<float>(columns)), h(1.0f / static_cast<float>(rows)){

	}
	std::vector<std::array<float,12>>frames;
protected:
	const float w;
	const float h;
};