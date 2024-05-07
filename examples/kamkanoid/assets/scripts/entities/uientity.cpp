#include "uientity.h"

UiEntity::UiEntity(Scene* scene) : GameObject(scene)
{
}

void UiEntity::beginPlay() 
{
	FontSerializer fontSerializer;
	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";
	addTransformComponent(new TransformComponent(glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* text = new TextComponent(fontDataPath,fontImagePath);
	text->setText("text is here");
	addTextComponent(text);
}
