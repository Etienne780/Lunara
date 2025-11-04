#include <SDL3/SDL.h>
#include <CoreLib/Log.h>
#include <Application.h>


#include "SDLCoreRenderer.h"

namespace SDLCore::Renderer {

	static std::shared_ptr<SDL_Renderer> m_renderer;

    static int m_strokeWidth = 1;
    static bool m_innerStroke = true;

    SDL_Renderer* GetActiveRenderer() {
        return m_renderer.get();
    }

    static std::shared_ptr<SDL_Renderer> GetActiveRenderer(const char* func) {
        if (!m_renderer) {
            Log::Error("SDLCore::Renderer::{}: Current renderer is null", func);
        }
        return m_renderer;
    }

    void SetWindowRenderer(WindowID winID) {
        if (winID.value == SDLCORE_INVALID_ID) {
            m_renderer.reset();
            return;
        }

        auto app = Application::GetInstance();
        auto win = app->GetWindow(winID);

        if (!win) {
            m_renderer.reset();
            return;
        }

        if (!win->HasRenderer()) {
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Renderer of window '{}' is null or destroyed!", win->GetName());
            m_renderer.reset();
            return;
        }

        std::shared_ptr<SDL_Renderer> rendererShared = win->GetSDLRenderer();
        if (!rendererShared) {
            Log::Error("SDLCore::Renderer::SetWindowRenderer: Renderer of window '{}' is null or destroyed!", win->GetName());
            m_renderer.reset();
            return;
        }

        m_renderer = rendererShared;
    }

    void Clear() {
        auto renderer = GetActiveRenderer("Clear");
        if (!renderer) 
            return;
        if (SDL_RenderClear(renderer.get()) < 0) {
            Log::Error("SDLCore::Renderer::Clear: Failed to clear renderer: {}", SDL_GetError());
        }
    }

    void Present() {
        auto renderer = GetActiveRenderer("Present");
        if (!renderer)
            return;
        if (SDL_RenderPresent(renderer.get()) < 0) {
            Log::Error("SDLCore::Renderer::Present: Failed to Present: {}", SDL_GetError());
        }
    }

    void SetViewport(int x, int y, int w, int h) {
        auto renderer = GetActiveRenderer("SetViewport");
        if (!renderer)
            return;

        SDL_Rect viewport{ x, y, w, h };
        if (SDL_SetRenderViewport(renderer.get(), &viewport) < 0) {
            Log::Error("SDLCore::Renderer::SetViewport: Failed to set viewport ({}, {}, {}, {}): {}",
                x, y, w, h, SDL_GetError());
        }
    }

    void ResetViewport() {
        auto renderer = GetActiveRenderer("ResetViewport");
        if (!renderer)
            return;

        if (SDL_SetRenderViewport(renderer.get(), nullptr) < 0) {
            Log::Error("SDLCore::Renderer::ResetViewport: Failed to reset viewport: {}", SDL_GetError());
        }
    }

    void SetBlendMode(bool enabled) {
        auto renderer = GetActiveRenderer("SetBlendMode");
        if (!renderer)
            return;

        SDL_BlendMode mode = enabled ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE;
        if (SDL_SetRenderDrawBlendMode(renderer.get(), mode) < 0) {
            Log::Error("SDLCore::Renderer::SetBlendMode: Failed to set blend mode {}: {}",
                enabled ? "BLEND" : "NONE", SDL_GetError());
        }
    }

    void SetBlendMode(BlendMode mode) {
        auto renderer = GetActiveRenderer("SetBlendMode");
        if (!renderer)
            return;
        if (SDL_SetRenderDrawBlendMode(renderer.get(), static_cast<SDL_BlendMode>(mode)) < 0) {
            Log::Error("SDLCore::Renderer::SetBlendMode: Failed to set blend mode {}: {}", static_cast<int>(mode), SDL_GetError());
        }
    }

    #pragma region Color

    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        auto renderer = GetActiveRenderer("SetColor");
        if (!renderer)
            return;
        if (SDL_SetRenderDrawColor(renderer.get(), r, g, b, a) < 0) {
            Log::Error("SDLCore::Renderer::SetColor: Failed to set color ({}, {}, {}, {}): {}", r, g, b, a, SDL_GetError());
        }
    }

    void SetColor(Uint8 r, Uint8 g, Uint8 b) {
        SetColor(r, g, b, 255);
    }

    void SetColor(Uint8 brightness, Uint8 alpha) {
        SetColor(brightness, brightness, brightness, alpha);
    }

    void SetColor(Uint8 brightness) {
        SetColor(brightness, brightness, brightness, 255);
    }

    void SetColor(const Vector4& rgba) {
        SetColor(static_cast<Uint8>(rgba.x), static_cast<Uint8>(rgba.y), static_cast<Uint8>(rgba.z), static_cast<Uint8>(rgba.w));
    }

    void SetColor(const Vector3& rgb) {
        SetColor(static_cast<Uint8>(rgb.x), static_cast<Uint8>(rgb.y), static_cast<Uint8>(rgb.z), 255);
    }

    #pragma endregion

    void SetStrokeWidth(int width) {
        if (width <= 0) 
            width = 1;
        m_strokeWidth = width;
    }

    void SetInnerStroke(bool value) {
        m_innerStroke = value;
    }

    #pragma region Primitives

    #pragma region Rectangle

    void FillRect(float x, float y, float w, float h) {
        auto renderer = GetActiveRenderer("FillRect");
        if (!renderer)
            return;
        SDL_FRect rect{ x, y, w, h };
        if (SDL_RenderFillRect(renderer.get(), &rect) < 0) {
            Log::Error("SDLCore::Renderer::FillRect: Failed to fill rect ({}, {}, {}, {}): {}", x, y, w, h, SDL_GetError());
        }
    }

    void FillRect(const Vector2& pos, float w, float h) {
        FillRect(pos.x, pos.y, w, h);
    }

    void FillRect(float x, float y, const Vector2& size) {
        FillRect(x, y, size.x, size.y);
    }

    void FillRect(const Vector2& pos, const Vector2& size) {
        FillRect(pos.x, pos.y, size.x, size.y);
    }

    void FillRect(const Vector4& trans) {
        FillRect(trans.x, trans.y, trans.x, trans.y);
    }

    void Rect(float x, float y, float w, float h) {
        auto renderer = GetActiveRenderer("Rect");
        if (!renderer) 
            return;

        for (int i = 0; i < m_strokeWidth; i++) {
            SDL_FRect rect;
            if (m_innerStroke) {
                rect = SDL_FRect{
                    x + i,
                    y + i,
                    w - 2 * i,
                    h - 2 * i
                };
            }
            else {
                rect = SDL_FRect{
                    x - i,
                    y - i,
                    w + 2 * i,
                    h + 2 * i
                };
            }

            if (rect.w <= 0 || rect.h <= 0)
                break;

            if (SDL_RenderRect(renderer.get(), &rect) < 0) {
                Log::Error("SDLCore::Renderer::Rect: Failed to draw rect at iteration {} ({}, {}, {}, {}): {}",
                    i, rect.x, rect.y, rect.w, rect.h, SDL_GetError());
                break;
            }
        }
    }

    void Rect(const Vector2& pos, float w, float h) {
        Rect(pos.x, pos.y, w, h);
    }

    void Rect(float x, float y, const Vector2& size) {
        Rect(x, y, size.x, size.y);
    }

    void Rect(const Vector2& pos, const Vector2& size) {
        Rect(pos.x, pos.y, size.x, size.y);
    }

    void Rect(const Vector4& trans) {
        Rect(trans.x, trans.y, trans.x, trans.y);
    }

    #pragma endregion

    #pragma region Line

    void Line(float x1, float y1, float x2, float y2) {
        auto renderer = GetActiveRenderer("Line");
        if (!renderer)
            return;

        if (m_strokeWidth <= 1) {
            SDL_RenderLine(renderer.get(), x1, y1, x2, y2);
            return;
        }

        float dx = x2 - x1;
        float dy = y2 - y1;
        float length = std::sqrt(dx * dx + dy * dy);
        if (length == 0.0f)
            return;

        dx /= length;
        dy /= length;

        float nx = -dy;
        float ny = dx;

        float halfStroke = m_strokeWidth / 2.0f;

        SDL_FPoint verts[4] = {
            { x1 + nx * halfStroke, y1 + ny * halfStroke },
            { x2 + nx * halfStroke, y2 + ny * halfStroke },
            { x2 - nx * halfStroke, y2 - ny * halfStroke },
            { x1 - nx * halfStroke, y1 - ny * halfStroke }
        };
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(renderer.get(), &r, &g, &b, &a);
        SDL_Vertex quad[4];
        for (int i = 0; i < 4; ++i) {
            quad[i].position.x = verts[i].x;
            quad[i].position.y = verts[i].y;
            quad[i].color = SDL_FColor{ static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a) };
        }

        int indices[6] = { 0, 1, 2, 2, 3, 0 };
        if (SDL_RenderGeometry(renderer.get(), nullptr, quad, 4, indices, 6) < 0) {
            Log::Error("SDLCore::Renderer::Line: Failed to draw thick line ({}, {}, {}, {}): {}", x1, y1, x2, y2, SDL_GetError());
        }
    }

    void Line(const Vector2& p1, float x2, float y2) {
        Line(p1.x, p1.y, x2, y2);
    }

    void Line(float x1, float y1, const Vector2& p2) {
        Line(x1, y1, p2.x, p2.y);
    }

    void Line(const Vector2& p1, const Vector2& p2) {
        Line(p1.x, p1.y, p2.x, p2.y);
    }

    void Line(const Vector4& poins) {
        Line(poins.x, poins.y, poins.z, poins.w);
    }

    #pragma endregion

    void Point(float x, float y) {
        auto renderer = GetActiveRenderer("Point");
        if (!renderer)
            return;

        if (SDL_RenderPoint(renderer.get(), x, y) < 0) {
            Log::Error("SDLCore::Renderer::Point: Failed to draw point ({}, {}): {}", x, y, SDL_GetError());
        }
    }

    #pragma endregion

}