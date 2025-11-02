#pragma once
#include <string>

namespace SDLCore {

	class Application;
	class Window {
	friend class Application;
	public:

	private:
		Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;
		
		std::string m_name = "Untitled";
		unsigned int m_width = 0;
		unsigned int m_height = 0;
	};

}