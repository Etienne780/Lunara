#include <cmath>
#include <vector>
#include <CoreLib/Math/Vector4.h>
#include "Lunara.h"

Lunara::Lunara()
    : Application("Lunara", SDLCore::Version(1, 0)) {
}

struct MovingRect {
    Vector4 rect; // x, y, w, h
    Vector2 velocity; // vx, vy
};

static SDLCore::WindowID winFillID;
static SDLCore::WindowID winStrokeID;
std::vector<MovingRect> movingRects;

void Lunara::OnStart() {
    auto* winFill = CreateWindow("FillRects", 800, 800);
    winFillID = winFill->GetID();
    winFill->SetOnClose([]() { winFillID.value = SDLCORE_INVALID_ID; });

    auto* winStroke = CreateWindow("StrokeRects", 800, 800);
    winStrokeID = winStroke->GetID();
    winStroke->SetOnClose([]() { winStrokeID.value = SDLCORE_INVALID_ID; });

    int count = 10000;
    for (int i = 0; i < count; ++i) {
        MovingRect mr;
        mr.rect = Vector4{ float(10 + i * 30), float(10 + i * 20), float(17 + i * 3.234f), float(16 + i * 2.43f) };
        mr.velocity = Vector2{ float((i % 3) + 1), float((i % 2) + 1) };
        movingRects.push_back(mr);
    }
}

void Lunara::OnUpdate() {
    if (GetWindowCount() <= 0) Quit();

    namespace RE = SDLCore::Renderer;

    double timeSec = SDLCore::Time::GetTimeSec();
    float stroke = std::sin(timeSec * 2) * 30;

    for (auto& mr : movingRects) {
        mr.rect.x += mr.velocity.x;
        mr.rect.y += mr.velocity.y;

        if (winStrokeID != SDLCORE_INVALID_ID) {
            auto* win = GetWindow(winStrokeID);
            if (win) {
                if (mr.rect.x <= 0 || mr.rect.x + mr.rect.z >= win->GetWidth()) mr.velocity.x *= -1;
                if (mr.rect.y <= 0 || mr.rect.y + mr.rect.w >= win->GetHeight()) mr.velocity.y *= -1;
            }
        }
    }

    if (winFillID != SDLCORE_INVALID_ID) {
        RE::SetWindowRenderer(winFillID);
        RE::SetColor(50, 50, 50);
        RE::Clear();

        RE::SetColor(0, 255, 0);
        std::vector<Vector4> fillRects;
        fillRects.reserve(movingRects.size());
        for (auto& mr : movingRects) fillRects.push_back(mr.rect);
        RE::FillRects(fillRects);

        RE::Present();
    }

    if (winStrokeID != SDLCORE_INVALID_ID) {
        RE::SetWindowRenderer(winStrokeID);
        RE::SetColor(0, 0, 50);
        RE::Clear();

        RE::SetStrokeWidth(std::abs(stroke));
        RE::SetInnerStroke(stroke > 0);
        RE::SetColor(255, 0, 0);
        std::vector<Vector4> strokeRects;
        strokeRects.reserve(movingRects.size());
        for (auto& mr : movingRects) strokeRects.push_back(mr.rect);
        RE::Rects(strokeRects);

        RE::Present();
    }

    Log::Print(SDLCore::Time::GetFrameRate());
}

void Lunara::OnQuit() {
}