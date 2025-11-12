#include <CoreLib/Log.h>
#include "types/Version.h"

namespace SDLCore {

	Version::Version(unsigned int version) 
		: m_versionType(VersionType::SINGLE_COMPONENT), m_major(version) {
	}
	
	Version::Version(unsigned int major, unsigned int minor) 
		: m_versionType(VersionType::DUAL_COMPONENT), m_major(major), m_minor(minor) {
	}

	Version::Version(unsigned int major, unsigned int minor, unsigned int patch) 
		: m_versionType(VersionType::SEMANTIC), m_major(major), m_minor(minor), m_patch(patch) {
	}

    std::string Version::ToString() const {
		if (m_versionType == VersionType::SINGLE_COMPONENT) {
			return FormatUtils::formatString("{}", m_major);
		}
		else if (m_versionType == VersionType::DUAL_COMPONENT) {
			return FormatUtils::formatString("{}.{}", m_major, m_minor);
		}
		return FormatUtils::formatString("{}.{}.{}", m_major, m_minor, m_patch);
    }

	VersionType Version::GetVersionType() const {
		return m_versionType;
	}

	unsigned int Version::GetVersion() const {
		if (m_versionType != VersionType::SINGLE_COMPONENT)
			Log::Warn("Version::GetVersion: called on non-single component version type: {}", m_versionType);
		return m_major;
	}

	unsigned int Version::GetMajor() const {
		if(m_versionType != VersionType::SEMANTIC && m_versionType != VersionType::DUAL_COMPONENT)
			Log::Warn("Version::GetMajor: called on non-semantic or non-dual component version type: {}", m_versionType);
		return m_major;
	}

	unsigned int Version::GetMinor() const {
		if (m_versionType != VersionType::SEMANTIC && m_versionType != VersionType::DUAL_COMPONENT)
			Log::Warn("Version::GetMajor: called on non-semantic or non-dual component version type: {}", m_versionType);
		return m_minor;
	}

	unsigned int Version::GetPatch() const {
		if (m_versionType != VersionType::SEMANTIC)
			Log::Warn("Version::GetPatch: called on non-semantic version type: {}", m_versionType);
		return  m_patch;
	}

}