#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <string>
#include <array>
#include <regex>
#include "..\..\Include\Enums\CommandType.h"


class CommandManager
{
public:

	// Inviting the user to write a command by the '$' symbol
	// Recieving list of words in line command.
	// Interpreting command args and calling appropriate command
	static void GetUserCommand(); 

private:
	// Array of valid commands keywords
	static const std::array<std::string, 7> valid_commands_;
	static const std::regex regex_user_input_;
};

#endif