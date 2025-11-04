#include "Lunara.h"


Lunara::Lunara() 
	: Application("Lunara", SDLCore::Version(1, 0)) {
}

SDLCore::Window* winLunara = nullptr;
SDLCore::Window* winZwei = nullptr;
void Lunara::OnStart() {
	winLunara = CreateWindow("Lunara", 200, 200);
	winZwei = CreateWindow("zwei", 200, 200);
}

void Lunara::OnUpdate() {
	if (GetWindowCount() <= 0)
		Quit();

	{
		namespace RE = SDLCore::Renderer;
		RE::SetWindowRenderer(winLunara);
		RE::SetColor(255, 0, 0);
		RE::Clear();
		// idk
		RE::Present();

		RE::SetWindowRenderer(winZwei);
		RE::SetColor(0, 0, 255);
		RE::Clear();
		// idk
		RE::Present();
	}
}

void Lunara::OnQuit() {
	
}