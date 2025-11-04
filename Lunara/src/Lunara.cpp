#include "Lunara.h"


Lunara::Lunara() 
	: Application("Lunara", SDLCore::Version(1, 0)) {
}

void Lunara::OnStart() {
	CreateWindow("Lunara", 200, 200);
	CreateWindow("zwei", 200, 200);

	auto window = AddWindow("drei", 300, 200);
	window->SetName("Gay")->SetHeight(500)->SetAlwaysOnTop(true);
	window->CreateWindow();
	window->CreateRenderer();
}

void Lunara::OnUpdate() {
	if (GetWindowCount() <= 0)
		Quit();
}

void Lunara::OnQuit() {
	
}