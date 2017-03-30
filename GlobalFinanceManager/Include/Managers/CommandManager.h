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
	typedef void(GlobalManager::*ManagerDelegate)(std::string&);

	// An attempt to interpret and invoke command on GlobalManager argument
	static bool Invoke(GlobalManager& global_manager, const std::string& command_identifier, std::string& command_params);

	// Logic for displaying advanced reference to the commands
	static bool AdvancedHelpHandler(const std::string& params);

protected:
	// Map of GlobalManager delegates
	static const std::map<std::string, ManagerDelegate> commands_delegates_;

	// Map of commands reference
	static const std::map<std::string, std::string> commands_references_;

	// Map of references to commands how-to-use
	static const std::regex regex_user_input_;

public:
	static constexpr char* help_command_ = "help";

	static constexpr char* balance_command_ = "balance";
	static constexpr char* get_command_ = "get";
	static constexpr char* add_command_ = "add";
	static constexpr char* edit_command_ = "edit";

	static constexpr char* balance_command_reference_ = "BALANCE REFERENCE";
	static constexpr char* get_command_reference_ = "GET REFERENCE";
	static constexpr char* add_command_reference_ = "ADD REFERENCE";
	static constexpr char* edit_command_refernce_ = "EDIT REFERENCE";

	static constexpr char* time_argument_prefix_ = "tm";;
	static constexpr char* type_argument_prefix_ = "tp";;
	static constexpr char* category_argument_prefix_ = "c";;
	static constexpr char* description_argument_prefix_ = "d";;
	static constexpr char* sum_argument_prefix_ = "s";

};

#endif