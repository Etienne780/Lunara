#pragma once
#include <string>
#include <CoreLib/FormatUtils.h>

namespace SDLCore {

	enum class VersionType
	{
		SINGLE_COMPONENT,   // e.g., "1"
		DUAL_COMPONENT,     // e.g., "1.2"
		SEMANTIC            // e.g., "1.2.3"
	};

	class Version {
	public:
		Version(unsigned int version);
		Version(unsigned int major, unsigned int minor);
		Version(unsigned int major, unsigned int minor, unsigned int patch);

		std::string ToString() const;

		VersionType GetVersionType() const;
		unsigned int GetVersion() const;
		unsigned int GetMajor() const;
		unsigned int GetMinor() const;
		unsigned int GetPatch() const;

	private:
		VersionType m_versionType = VersionType::SINGLE_COMPONENT;
		unsigned int m_major = 0;
		unsigned int m_minor = 0;
		unsigned int m_patch = 0;
	};

}

template<>
static inline std::string FormatUtils::toString<SDLCore::Version>(SDLCore::Version value) {
	return value.ToString();
}

template<>
static inline std::string FormatUtils::toString<SDLCore::VersionType>(SDLCore::VersionType value) {
	switch (value) {
	case SDLCore::VersionType::SINGLE_COMPONENT: return "SINGLE_COMPONENT";
	case SDLCore::VersionType::DUAL_COMPONENT: return "DUAL_COMPONENT";
	case SDLCore::VersionType::SEMANTIC: return "SEMANTIC";
	}
	return "UNKNOWN";
}
