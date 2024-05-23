#pragma once
#include <engine/core/gameobject.h>

class PlayerKeyframes : public Keyframes {
public:
	PlayerKeyframes();
private:
};

class Player : public GameObject {
public:
	Player(Scene* scene);
	void beginPlay() override;
};
