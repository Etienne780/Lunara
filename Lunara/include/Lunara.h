#pragma once
#include <SDLCoreLib/Application.h>
#include <SDLCoreLib/ExtraTypes.h>
#include <CoreLib/Log.h>

class Lunara : public SDLCore::Application {
public:
	Lunara();
	
	void OnStart() override;
	void OnUpdate() override;
	void OnQuit() override;
	
private:
	
};