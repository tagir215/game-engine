#include <engine/application.h>

class MyGame : public engine::Application {
public:
	MyGame() : engine::Application(800, 600, "Sandbox1") {}
	///
	/// \brief Virtual function update, which is needed to implement in derived class.
	/// \param deltaTime
	///
	virtual void update(float deltaTime) {
		// TODO: Update logic comes here
	}

	virtual void render() {
		// TODO: Redner objects using renderer methods
	}
private:
};

int main() {
	MyGame game;
	return game.run();
}
