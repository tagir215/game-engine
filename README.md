# Tiimi 1

[![pipeline status](https://repo.kamit.fi/ttv22sp_pelimoottoriohjelmointi/tiimi6/badges/main/pipeline.svg)](https://repo.kamit.fi/ttv22sp_pelimoottoriohjelmointi/tiimi6/-/commits/main)

- TODO: Listaa tähän ryhmän jäsenten koko nimi ja rooli (lead/dev)

# Projektiopinnot 2

Tavoitteet: Opiskelija osaa tiimin jäsenenä suunnitella ja toteuttaa yksinkertaisen grafiikkamoottorin.
Edeltävä osaaminen: Ohjelmoinnin perusteet, Olio-ohjelmoinnin perusteet, C++, Projektiopinnot 1
Laajuus: 6 op ~162 h opiskelijan työtä

Sisältö: Grafiikkamoottorin suunnittelu ja toteutus tiimeissä. Liittyy kurssiin "Grafiikkamoottorin ohjelmointi".

Projektin sisältö ja vaatimukset:
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
	- Engine architecture example
		- Application
		- SFMLRenderer
		- SFMLAudio
		- GameObject / Entity
		- SceneManager
		- Layer
		- LayerTiles
		- PhysicsSystem
	- Lisää ominaisuuksia, jotta tuntikirjanpito täyttyy
	- Toteuta 2 esimerkkipeliä, referenssinä
		- Arkanoid
		- Pacman
		- Donkey Kong
	- UML-kaaviot luokista .md tiedostoon
		- kaaviot enginen luokista
		- kaaviot pelien luokista
	- commitit pidettävä asiallisina

