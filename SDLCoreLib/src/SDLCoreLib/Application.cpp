#include "Application.h"
#include "Version.h"

namespace SDLCore {

    Application::Application(std::string& name, Version& version) 
        : m_name(name), m_version(version) {
    }

    Application::Application(std::string&& name, Version&& version)
        : m_name(std::move(name)), m_version(std::move(version)) {
    }

}