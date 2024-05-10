#include "scoresystem.h"
#include "../entities/projectileentity.h"
#include <string>
#include <engine/core/scenemanager.h>

void ScoreSystem::onUpdate(float deltaTime)
{
	for (GameObject* object : gameObjects) {
		if (object->getTextComponent() == nullptr && object->getVelocityComponent().linearVelocity.y == 0) {
			continue;
		}
		ProjectileEntity* projectile = dynamic_cast<ProjectileEntity*>(object);
		if (projectile != nullptr) {
			if (projectile->updateScore) {
				currentScore += 10;
				if (currentScore > highScore) {
					highScore = currentScore;
				}
				if (currentScore >= 100) {
					SceneManager::getInstance().setScene("level_2");
				}
				projectile->updateScore = false;
			}
		}
		else if(currentScore != oldScore){
			if (object->getTags().find("score") != object->getTags().end()) {
				object->getTextComponent()->setText(std::to_string(currentScore));
			}
			if (object->getTags().find("highscore") != object->getTags().end()) {
				object->getTextComponent()->setText(std::to_string(highScore));
				oldScore = currentScore;
			}
		}
	}
}
