#pragma once
#include <SDL3/SDL.h>

inline constexpr unsigned int SDLCORE_INVALID_ID = std::numeric_limits<unsigned int>::max();
inline constexpr int APPLICATION_FPS_UNCAPPED = 0;
inline constexpr int APPLICATION_FPS_VSYNC_ON = -1;
inline constexpr int APPLICATION_FPS_VSYNC_ADAPTIVE_ON = -2;

namespace SDLCore {

	typedef int SDLResult;

	template<typename Tag>
	struct SDLCoreID {
		unsigned int value = SDLCORE_INVALID_ID;

		constexpr SDLCoreID() = default;
		explicit constexpr SDLCoreID(unsigned int v) : value(v) {}

		constexpr bool operator==(unsigned int other) const { return value == other; }
		constexpr bool operator!=(unsigned int other) const { return value != other; }
		constexpr bool operator<(unsigned int other) const { return value < other; }
		constexpr bool operator>(unsigned int other) const { return value > other; }
		constexpr bool operator<=(unsigned int other) const { return value <= other; }
		constexpr bool operator>=(unsigned int other) const { return value >= other; }

		constexpr bool operator==(const SDLCoreID& other) const { return value == other.value; }
		constexpr bool operator!=(const SDLCoreID& other) const { return value != other.value; }
		constexpr bool operator<(const SDLCoreID& other) const { return value < other.value; }
		constexpr bool operator>(const SDLCoreID& other) const { return value > other.value; }
		constexpr bool operator<=(const SDLCoreID& other) const { return value <= other.value; }
		constexpr bool operator>=(const SDLCoreID& other) const { return value >= other.value; }

		explicit constexpr operator bool() const { return value != 0; }
	};

	struct WindowTag {};
	using WindowID = SDLCoreID<WindowTag>;

}

template<>
static inline std::string FormatUtils::toString<SDLCore::SDLCoreID<SDLCore::WindowTag>>(SDLCore::WindowID id) {
	return FormatUtils::toString(id.value);
}

namespace std {
	template<typename Tag>
	struct hash<SDLCore::SDLCoreID<Tag>> {
		size_t operator()(const SDLCore::SDLCoreID<Tag>& id) const noexcept {
			return std::hash<unsigned int>{}(id.value);
		}
	};
}