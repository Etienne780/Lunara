#include <SDL3/SDL.h>
#include <CoreLib/Log.h>
#include <Application.h>


#include "SDLCoreRenderer.h"

namespace SDLCore::Renderer {

	static std::weak_ptr<SDL_Renderer> m_renderer;

    SDL_Renderer* GetActiveRenderer() {
        return m_renderer.lock().get();
    }

    static bool IsRendererNull(SDL_Renderer*& out, const char* func) {
        out = m_renderer.lock().get();
        if (!out)
            Log::Error("SDLCore::Renderer::{}: Current renderer is null", func);
        return out == nullptr;
    }

    void SetWindowRenderer(WindowID winID) {
        auto app = Application::GetInstance();
        auto win = app->GetWindow(winID);

        if (!win) {
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Cant set window renderer, window is null!");
            return;
        }

        m_renderer = win->GetSDLRenderer();
        if (!m_renderer.lock())
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Cant set window renderer, renderer of window '{}' is null!", win->GetName());
    }

    void SetWindowRenderer(Window* win) {
        if (!win) {
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Cant set window renderer, window is null!");
            return;
        }

        m_renderer = win->GetSDLRenderer();
        if (!m_renderer.lock())
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Cant set window renderer, renderer of window '{}' is null!", win->GetName());
    }

    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        SDL_Renderer* renderer = nullptr;
        if (IsRendererNull(renderer, "SetColor"))
            return;

        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }

    void SetColor(Uint8 r, Uint8 g, Uint8 b) {
        SetColor(r, g, b, 255);
    }

    void SetColor(const Vector4& rgba) {
        SetColor(static_cast<Uint8>(rgba.x), static_cast<Uint8>(rgba.y), static_cast<Uint8>(rgba.z), static_cast<Uint8>(rgba.w));
    }

    void SetColor(const Vector3& rgb) {
        SetColor(static_cast<Uint8>(rgb.x), static_cast<Uint8>(rgb.y), static_cast<Uint8>(rgb.z), 255);
    }

    void Clear() {
        SDL_Renderer* renderer = nullptr;
        if (IsRendererNull(renderer, "Clear"))
            return;
        SDL_RenderClear(renderer);
    }

    void Present() {
        SDL_Renderer* renderer = nullptr;
        if (IsRendererNull(renderer, "Present"))
            return;
        SDL_RenderPresent(renderer);
    }

}