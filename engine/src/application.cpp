#include <engine/application.h>

namespace engine {

	Application::Application(int sizeX, int sizeY, const std::string& title)
		: m_renderer(sizeX, sizeY, title) {
	}


	Application::~Application() {

	}


	void Application::stop() {
		m_running = false;
	}

	int Application::run() {
		m_running = true;
		sf::Clock frameTimer;
		while(m_renderer.isWindowOpen() && m_running) {
			float deltaTime = frameTimer.getElapsedTime().asSeconds();
			frameTimer.restart();
			update(deltaTime);
			m_renderer.onBeginFrame();
			render();
			m_renderer.onEndFrame();
		}
		return 0;
	}

} // End - namespace engine
