#include "uientity.h"

UiEntity::UiEntity(Scene* scene) : GameObject(scene)
{
	FontSerializer fontSerializer;
	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";
	TextComponent* text = new TextComponent(fontDataPath,fontImagePath);
	text->setText("text is here");
	addTextComponent(text);
	addTransformComponent(TransformComponent(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
}
