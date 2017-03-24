#include "..\Include\Application.h"
#include "..\Include\Managers\CommandManager.h"
#include <iostream>

Application::Application()
{
	Initialize();
}

bool Application::Iterate()
{
	return CommandManager::GetUserCommand(*manager);
}

Application::~Application()
{
	Terminate();
}

void Application::Initialize()
{
	manager = new GlobalManager();
}

void Application::Terminate()
{
	delete manager;
}

void Application::Help()
{
	std::cout << "\n\nHELP REFERENCE\n\n";
}