#include "player.h"
#include <../assets/basicShapes/plane.h>

Player::Player(Scene* scene) : GameObject(scene)
{
	TextureManager textureManager;
	TextureComponent* texture = textureManager.loadTextureFromPath("../../../../engine/assets/textures/walk-basic.png");
	Plane* mesh = new Plane();
	texture->setKeyframes(new PlayerKeyframes());
	setTextureComponent(texture);
	setMeshComponent(mesh);
}

void Player::beginPlay()
{
	createComponent<PhysicsComponent>(150, true, 0.3f, true, 0, getTransformComponent()->scale, false);
	createComponent<InputComponent>();
	createComponent<VelocityComponent>(0, 0, 0);
	createComponent<ShaderComponent>(0);
}

PlayerKeyframes::PlayerKeyframes() : Keyframes(4, 2) {
	for (int y = 1; y >= 0; y--) {
		for (int x = 0; x < 4; x++) {
			frames.push_back(
				{
					x * w  , y * h,      //left-bottom
					x * w + w, y * h,      //right-bottom
					x * w + w, y * h + h,    //right-top
					x * w  , y * h,      //left-bottom
					x * w + w, y * h + h,    //right-top
					x * w  , y * h + h     //left-top
				}
			);
		};
	}

}
