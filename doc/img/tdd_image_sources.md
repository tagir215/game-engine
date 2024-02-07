# TDD Architecture

TODO: Muuta suunnitelmien mukaiseksi

# Engine

```
@startuml
class Application <<engine>>
class GameObject <<engine>>
class Scene <<engine>>
class Layer <<engine>>
class SFMLRenderer <<engine>>
class SFMLAudio <<engine>>
class LayerTiles <<engine>>
class PhysicsSystem <<engine>>

Application "1" *-- "1" Scene
Application "1" *-- "1" SFMLRenderer
Application "1" *-- "1" SFMLAudio
Application "1" *-- "1" PhysicsSystem

Application : Application()
Application : run()
Application : getScene() : Scene&
Application : getRenderer() : SFMLRenderer&
Application : getAudio() : SFMLAudio&
Application : virtual void update(deltaTime) = 0
Application : virtual void render() = 0

GameObject : virtual void update(deltaTime) = 0

Scene "1" *-- "*" Layer
Layer "1" *-- "*" GameObject
Layer "1" *-- "1" LayerTiles

Scene : reset()
Scene : spawnToLayer<GameObejctType>(layerId, constructParams) : std::shared_ptr<GameObejctType>
Scene : destroy(std::shared_ptr<GameObject>)
Scene : loadMap(fileName) : bool
Scene : renderScene(SFMLRenderer&)

SFMLRenderer : SFMLRenderer(textureFileNames,fontFileNames)
SFMLRenderer : setView(position,size)
SFMLRenderer : clearScreen(color)
SFMLRenderer : renderSprite(position,size,rotation,textureId)
SFMLRenderer : renderSprite(position,size,rotation,textureId,clipStart,clipSize)
SFMLRenderer : renderText(fontId, text, position, size)
SFMLRenderer : renderTiles(...)

SFMLAudio : SFMLAudio(audioFileNames)
SFMLAudio : playSound(soundId)

Layer : renderLayers(SFMLRenderer&)

@enduml
```

# Engine components

```
@startuml
class Transform <<engine>>
Transform : vec2 position
Transform : vec2 size
Transform : float rotation

class Sprite <<engine>>
Sprite : int textureId

@enduml
```
