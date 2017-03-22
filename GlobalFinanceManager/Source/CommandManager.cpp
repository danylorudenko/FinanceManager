#include <algorithm>
#include "..\Include\Managers\CommandManager.h"
#include <iostream>
#include <cctype>

const std::array<std::string, 7> CommandManager::valid_commands_ = { "help", "balance", "add", "get", "search", "edit", "exit" };
const std::regex regex_user_input_ = std::regex
(
	"([a-z]+)"
	"([\\s]{1})"
	"([\\s\\w]+)"
);

void CommandManager::GetUserCommand()
{
	
}