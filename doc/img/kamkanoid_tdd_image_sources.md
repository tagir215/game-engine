```
@startuml
class Application <<engine>>
class GameObject <<engine>>

GameObject <|-- Player
GameObject <|-- Enemy
GameObject <|-- Item
GameObject <|-- Projectile

Application <|-- MyGameApp

Application : virtual void update(deltaTime) = 0
Application : virtual void render() = 0

GameObject : virtual void update(deltaTime) = 0

MyGameApp : virtual void update(deltaTime)
MyGameApp : virtual void render()

Player : virtual void update(deltaTime)
Enemy : virtual void update(deltaTime)
Item : virtual void update(deltaTime)
Projectile : virtual void update(deltaTime)

@enduml
```

```
@startuml
class GameObject <<engine>>

GameObject <|-- Player

Player : virtual void update(deltaTime)

Player o-- Transform
Player o-- Sprite

@enduml
```

```
@startuml
class Application <<engine>>

Application <|-- KamkanoidApp

Application : virtual void update(deltaTime) = 0
Application : virtual void render() = 0

KamkanoidApp : virtual void update(deltaTime)
KamkanoidApp : virtual void render()

@enduml
```
