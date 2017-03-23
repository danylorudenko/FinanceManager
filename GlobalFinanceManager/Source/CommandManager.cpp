#include "..\Include\Managers\CommandManager.h"
#include "..\Include\Managers\GlobalManager.h"
#include <iostream>

//const std::array<std::string, 7> CommandManager::valid_commands_ = { "help", "balance", "add", "get", "search", "edit", "exit" };

const std::map<std::string, CommandManager::ManagerDelegate> CommandManager::valid_commands_ 
{
	{ "balance", GlobalManager::DisplayBalance },
	{ "add", GlobalManager::AddEntry },
	{ "get", GlobalManager::GetRecords },
	{ "search", GlobalManager::GlobalSearch },
	{ "edit", GlobalManager::EditEntry }
};

const std::regex CommandManager::regex_user_input_ = std::regex
(
	"([a-z]+)"
	"([\\s]{1})"
	"([\\s\\w]+)"
);

void CommandManager::GetUserCommand(GlobalManager& manager)
{
	std::string input_buffer;
	std::getline(std::cin, input_buffer);

	std::cmatch result;

	if (std::regex_match(input_buffer.c_str(), result, regex_user_input_)) {
		
		Invoke(manager, result[1].str, result[2].str);
	}
}

bool CommandManager::Invoke(GlobalManager& global_manager, const std::string& command_identifier, const std::string& command_args)
{
	const CommandManager::ManagerDelegate* manager_delegate;

	try {
		if (command_identifier == "exit") {
			// Exit the app
			return false;
		}
		else if (command_identifier == "help") {
			// Help reference
		}

		manager_delegate = &valid_commands_.at(command_identifier);
		(global_manager.**manager_delegate)(command_args);
		return true;
	}
	catch (std::out_of_range e) {
		std::cout << "There is no such command. Type \"help\" to see the reference.\n";
	}

	return true;
}