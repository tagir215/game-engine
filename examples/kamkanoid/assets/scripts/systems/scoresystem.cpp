#include "scoresystem.h"
#include "../entities/projectileentity.h"
#include <string>
#include <engine/core/gamemode.h>

void ScoreSystem::onUpdate(float deltaTime)
{
	for (GameObject* object : gameObjects) {
		if (object->getTextComponent() == nullptr && object->getVelocityComponent().linearVelocity.y == 0) {
			continue;
		}
		if (highScore != GameMode::getInstance().getPlayerState().getScore()) {
			highScore = GameMode::getInstance().getPlayerState().getScore();
		}
		ProjectileEntity* projectile = dynamic_cast<ProjectileEntity*>(object);
		if (projectile != nullptr) {
			if (projectile->updateScore) {
				currentScore += 10;
				if (currentScore > highScore) {
					highScore = currentScore;
					GameMode::getInstance().getPlayerState().setScore(currentScore);
				}
				if (currentScore >= 100) {
					GameMode::getInstance().getSceneManager().setScene("level_2");
				}
				projectile->updateScore = false;
			}
		}
		else {
			if (currentScore != oldScore && object->getTags().contains("score")) {
				object->getTextComponent()->setText(std::to_string(currentScore));
				oldScore = currentScore;
			}
			if (object->getTags().contains("highscore")) {
				object->getTextComponent()->setText(std::to_string(highScore));
			}
		}
	}
}
