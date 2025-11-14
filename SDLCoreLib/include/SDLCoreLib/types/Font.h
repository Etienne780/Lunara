#pragma once
#include <vector>
#include <unordered_map>
#include "SDLCoreTypes.h"

struct TTF_Font;

namespace SDLCore {

	class Font {
	public:
		Font() = default;
		Font(const SystemFilePath& path, std::vector<float> sizes = {}, size_t cachedSizes = 10);

		Font* SelectSize(float size);
		Font* SetCachSize(size_t size);
		Font* Setpath(const SystemFilePath& path);
		Font* Clear();

		float GetSelectedSize() const;
		SystemFilePath GetSystemPath() const;
		std::string GetFileName() const;
		size_t GetCachSize() const;
		size_t GetNumberOfCachedFontAssets() const;

	private:
		class FontAsset {
		public:
			FontAsset(TTF_Font* font, size_t size);
			~FontAsset();

			FontAsset(const FontAsset&) = delete;
			FontAsset& operator=(const FontAsset&) = delete;

			FontAsset(FontAsset&& other) noexcept;
			FontAsset& operator=(FontAsset&& other) noexcept;

			float fontSize = -1;
			size_t lastUseTick = 0;
			TTF_Font* ttfFont = nullptr;

		private:
			void MoveFrom(FontAsset&& other) noexcept;
			void Cleanup();
		};

		SystemFilePath m_path;
		std::vector<FontAsset> m_fontAssets;
		size_t m_maxFontSizesCached = 10;/**< number of font sizes that get stored at the same time */

		size_t m_globalAccessCounter = 0;
		float m_selectedSize = -1;

		FontAsset* GetFontAsset(float size);
		bool CreateFontAsset(float size);
		void CalculateCachedFonts();
	};

}
