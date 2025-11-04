#include "Lunara.h"


Lunara::Lunara() 
	: Application("Lunara", SDLCore::Version(1, 0)) {
}

SDLCore::WindowID winLunara;
SDLCore::WindowID winZwei;
void Lunara::OnStart() {
	winLunara = CreateWindow("Lunara", 200, 200)->GetID();
	winZwei = CreateWindow("zwei", 200, 200)->GetID();
}

void Lunara::OnUpdate() {
	if (GetWindowCount() <= 0)
		Quit();

	{
		namespace RE = SDLCore::Renderer;
		RE::SetWindowRenderer(winLunara);
		RE::SetColor(255, 0, 0);
		RE::Clear();

		RE::SetColor(0, 255, 0);
		RE::FillRect(100, 100, 50, 50);

		RE::Present();

		RE::SetWindowRenderer(winZwei);
		RE::SetColor(0, 0, 255);
		RE::Clear();

		RE::SetColor(0, 255, 0);
		RE::FillRect(100, 100, 50, 50);

		RE::Present();
	}
}

void Lunara::OnQuit() {
	
}