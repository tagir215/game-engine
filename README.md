# Tiimi 1

[![pipeline status](https://repo.kamit.fi/ttv22sp_pelimoottoriohjelmointi/tiimi6/badges/main/pipeline.svg)](https://repo.kamit.fi/ttv22sp_pelimoottoriohjelmointi/tiimi6/-/commits/main)

- TODO: Listaa tähän ryhmän jäsenten koko nimi ja rooli (lead/dev)

# Projektiopinnot 2

Tavoitteet: Opiskelija osaa tiimin jäsenenä suunnitella ja toteuttaa yksinkertaisen grafiikkamoottorin.
Edeltävä osaaminen: Ohjelmoinnin perusteet, Olio-ohjelmoinnin perusteet, C++, Projektiopinnot 1
Laajuus: 6 op ~162 h opiskelijan työtä

Sisältö: Grafiikkamoottorin suunnittelu ja toteutus tiimeissä. Liittyy kurssiin "Grafiikkamoottorin ohjelmointi".

# Projektin sisältö ja vaatimukset:
- Tavoitteena tehdä 2D-pelimoottori, jossa seuraavat kansiorakenteet:
	- doc/
		- tuntikirjanpito, laske loppuun tunnit yhteensä (tuntikirjanpidossa pitää olla selkeät työtehtävät näkyvissä)
		- muita kansioita/tiedostoja tarpeen vaatiessa
	- engine/
		- src/ = .cpp lähdekooditiedostot
		- include/ = .h tiedostot
		- ext/ = third-party libraries
	- examples/ = Tähän kansioon peliprojektit, jotka käyttävät enginen luokkia
		- pelidemo1
		- pelidemo2
	- sandboxes/ = Testaus ympäristö esim. eri kirjastoille
		- TestProject1
		- AudioTest1
		- ...
	- README.md
- Lisää ominaisuuksia, jotta tuntikirjanpito täyttyy
- Toteuta 2 esimerkkipeliä
- UML-kaaviot luokista .md tiedostoon
	- kaaviot enginen luokista
	- kaaviot pelien luokista
- commitit pidettävä asiallisina

# Ohjelmistoarkkitehtuuri

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

Alustavat moottorin luokkien nimet ja metodit (luokat engine kansiossa):

![](img/engine_classes.png "Moottorin luokkakaavio")

# Esimerkkipelin arkkitehtuuri

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

![](img/example_game_classes.png "Esimerkkipelin luokkakaavio")

Esimerkkipelisovellus ja sen luokka käyttävät enginen Application luokkaa sovelluksen tekemiseen tyyliin:
- GameApplication : public engine::Application

Pelikohtaiset peliobjektit käyttävät enginen GameObject luokkaa kantaluokkana tyyliin:
- Player : public engine::GameObject
- Enemy : public engine::GameObject
- jne...

# Toteutettavat esimerkkipelit

## Peli 1: kamkanoid
Yksinkertainen peli ilman grid mappia. Tämä sisältää myös esimerkin Main menusta ja High score taulukosta. Refenssipelinä Arkanoid (2 leveliä).  

## Peli 2: kamkman
Grid map pohjainen top-down peli, jossa pelin mappi luodaan koodtaulukolla. Refereinssipelinä Pacman (2 leveliä).

## Peli 3: kamkikong
Grid map pohjainen platformer, jossa pelin mappi ladataan Tiled työkalun tmx-formaatissa. Referenssipelinä Donkey Kong (2 leveliä).   