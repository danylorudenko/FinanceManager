#include "..\Include\Managers\CommandManager.h"
#include "..\Include\Managers\GlobalManager.h"
#include "..\Include\Application.h"
#include <iostream>

const std::string CommandManager::help_command_ = "help";

const std::string CommandManager::balance_command_ = "balance";
const std::string CommandManager::get_command_ = "get";
const std::string CommandManager::add_command_ = "add";
const std::string CommandManager::edit_command_ = "edit";

const std::string CommandManager::balance_command_reference_ = "HOW TO USE BALANCE";
const std::string CommandManager::get_command_reference_ = "HOW TO USE GET";
const std::string CommandManager::add_command_reference_ = "HOW TO USE ADD";
const std::string CommandManager::edit_command_refernce_ = "HOW TO USE EDIT";

const std::map<std::string, CommandManager::ManagerDelegate> CommandManager::commands_delegates_
{
	{ balance_command_, &GlobalManager::DisplayBalance },
	{ add_command_, &GlobalManager::AddEntry },
	{ get_command_, &GlobalManager::GetRecords },
	{ edit_command_, &GlobalManager::EditEntry }
};

const std::map<std::string, std::string> CommandManager::commands_references_
{
	{ balance_command_, balance_command_reference_ },
	{ get_command_, get_command_reference_ },
	{ add_command_, add_command_reference_ },
	{ edit_command_,  edit_command_refernce_ }
};

const std::regex CommandManager::regex_user_input_ = std::regex
(
	"([a-z]+)"
	"([\\s]{1})"
	"([\\S\\s]+)"
);

bool CommandManager::GetUserCommand(GlobalManager& manager)
{
	std::cout << "$ ";
	
	std::string input_buffer;
	std::getline(std::cin, input_buffer);

	if (input_buffer == "exit") {
		return false;
	}
	else if (input_buffer == "help") {
		Application::Help();
		return true;
	}

	std::cmatch result;

	if (std::regex_match(input_buffer.c_str(), result, regex_user_input_)) {
		if (result[1] == help_command_) {
			return AdvancedHelpHandler(result[3]);
		}

		return Invoke(manager, result[1], result[3].str());
	}

	std::cout << "Invalid format of command.\n";
	return true;
}

bool CommandManager::AdvancedHelpHandler(const std::string& args)
{
	try {
		const std::string& reference = commands_references_.at(args);
		std::cout << reference << std::endl;
	}
	catch (std::out_of_range e) {
		std::cout << "There is no reference for this command. Type \"help\" to see full reference.\n";
	}
	
	return true;
}

bool CommandManager::Invoke(GlobalManager& global_manager, const std::string& command_identifier, std::string& command_args)
{
	const CommandManager::ManagerDelegate* manager_delegate;

	try {
		manager_delegate = &commands_delegates_.at(command_identifier);
		(global_manager.**manager_delegate)(command_args);
		return true;
	}
	catch (std::out_of_range e) {
		std::cout << "There is no such command. Type \"help\" to see the reference.\n";
	}

	return true;
}