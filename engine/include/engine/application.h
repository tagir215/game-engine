#pragma once
#include <engine/sfml_renderer.h>

namespace engine {

///
/// \brief The Application class
///
class Application {
public:
	///
	/// \brief Application constructor
	///
	Application(int sizeX, int sizeY, const std::string& title);

	///
	/// \brief Application destructor
	///
	~Application();

	///
	/// \brief Application run called by main function.
	///
	int run();

	///
	/// \brief Stops the application.
	///
	void stop();

	///
	/// \brief getRenderer
	/// \return
	///
	inline SFMLRenderer& getRenderer() {
		return m_renderer;
	}

	///
	/// \brief Virtual function update, which is needed to implement in derived class.
	/// \param deltaTime
	///
	virtual void update(float deltaTime) = 0;

	///
	/// \brief Virtual function render, which is needed to implement in derived class.
	///
	virtual void render() = 0;

private:
	Application();
	Application(const Application&);
	Application& operator=(const Application&);

	bool m_running = false;
	SFMLRenderer m_renderer;
};

} // End - namespace engine

