#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <string>
#include <map>
#include <regex>
#include "..\..\Include\Enums\CommandType.h"

class GlobalManager;

class CommandManager
{
public:

	// Inviting the user to write a command by the '$' symbol
	// Recieving list of words in line command.
	// Interpreting command args and calling appropriate command
	static bool GetUserCommand(GlobalManager& manager); 

private:
	typedef void(GlobalManager::*ManagerDelegate)(const std::string&);

	static bool Invoke(GlobalManager& global_manager, const std::string& command_identifier, const std::string& command_params);

private:
	// Array of valid commands keywords
	static const std::map<std::string, ManagerDelegate> valid_commands_;
	static const std::regex regex_user_input_;
};

#endif