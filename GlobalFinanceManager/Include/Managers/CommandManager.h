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

protected:
	// Delegate to invoke GlobalManager instance commands
	typedef void(GlobalManager::*ManagerDelegate)(const std::string&);

	// An attempt to interpret and invoke command on GlobalManager argument
	static bool Invoke(GlobalManager& global_manager, const std::string& command_identifier, const std::string& command_params);

	// Logic for displaying advanced reference to the commands
	static bool AdvancedHelpHandler(const std::string& params);

protected:
	// Map of GlobalManager delegates
	static const std::map<std::string, ManagerDelegate> commands_delegates_;

	// Map of commands reference
	static const std::map<std::string, std::string> commands_references_;

	// Map of references to commands how-to-use
	static const std::regex regex_user_input_;

	static const std::string help_command_;

	static const std::string balance_command_;
	static const std::string get_command_;
	static const std::string add_commnad_;
	static const std::string search_command_;
	static const std::string edit_command_;

	static const std::string balance_command_reference_;
	static const std::string get_command_reference_;
	static const std::string add_command_reference_;
	static const std::string search_command_reference_;
	static const std::string edit_command_refernce_;

};

#endif