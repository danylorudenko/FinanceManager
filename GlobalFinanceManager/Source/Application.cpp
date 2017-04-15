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
	std::cout << " === FINANCE MANAGER BETA === \n\n"
		"You should better expand the console window for the comfortable use.\n"
		"Type \"help\" to see the reference and to start managing you finances!\n" << std::endl;
}

void Application::Terminate()
{
	delete manager;
}

void Application::Help()
{
	std::cout <<
		"    === Available commands ===\n\n\n"
		"add [param-id:value], [param-id:value], ...      Add new finance entry to the manager.\n"
		"                                                 Define additional attributes with special params.\n"
		"                                                 (see params reference for details)\n\n"
		"balance [/tm:XX] or [all]                        Use balance with /tm param to display balance for the last XX days.\n"
		"                                                 Use balance with \"all\" param to display global balance.\n\n"
		"help [command-id]                                Get the reference to the specified command.\n"
		"                                                 Leave the parameter empty to see the list\n"
		"                                                 of all available commands.\n\n"
		"get /tm:XX, [param-id:value], ...                Get the list of finance records fith the specified request\n"
		"                                                 /tm:XX is an obligatory parameter. Put number of days instead of XX\n"
		"                                                 to set the starting date of the request.\n"
		"                                                 You can use other params to customize the request.\n"
		"                                                 (see params reference for details)\n\n"
		"edit [id] [param-id:value]                       Edit a finance entry with the specified id.\n"
		"                                                 You can use \"edit\" only after commands which display\n"
		"                                                 entries as a numerated list.\n"
		"                                                 Provide params to modify specified entry.\n"
		"                                                 (see params reference for details)\n\n";
}