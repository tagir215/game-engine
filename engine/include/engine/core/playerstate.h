#pragma once

class PlayerState {
public:
	float getScore() const {
		return score;
	}
	void setScore(float score) {
		this->score = score;
	}
private:
	float score;
};
