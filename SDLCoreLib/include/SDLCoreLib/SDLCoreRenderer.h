#pragma once
#include <CoreLib/Math/Vector3.h>
#include <CoreLib/Math/Vector4.h>
#include "Window.h"

namespace SDLCore::Renderer {

	SDL_Renderer* GetActiveRenderer();

	/**
	* @brief Sets the SDL renderer associated with a given window ID as the current renderer.
	* @param winID The unique ID of the target window.
	*
	* The function retrieves the window from the application instance using its ID.
	* If the window or its renderer is invalid, it logs an error message.
	*/
	void SetWindowRenderer(WindowID winID);

	/**
	* @brief Sets the SDL renderer of the given window as the current renderer.
	* @param win Pointer to the window object.
	*
	* Checks for a valid window and its renderer.
	* Logs an error if either is null.
	*/
	void SetWindowRenderer(Window* win);

	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetColor(const Vector4& rgba);
	void SetColor(const Vector3& rgb);

	void Clear();
	void Present();
}