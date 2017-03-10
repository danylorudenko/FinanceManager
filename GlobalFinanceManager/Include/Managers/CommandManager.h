#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <list>
#include <string>
#include <array>
#include "..\..\Include\Enums\CommandType.h"


class CommandManager
{

public:
	// Access to the singletone instance
	static CommandManager& Instance();

	// Inviting the user to write a command by the '$' symbol
	// Recieving list of words in line command.
	// Interpreting command args and calling appropriate command
	std::string GetUserCommand(); 

private:
	// Array of valid commands keywords
	const std::array<std::string, 5> validCommands = { "help", "display_finances", "add_income", "add_spendings", "exit" };

	// Singletone instance
	static CommandManager* instance;

	// Buffer for the arguments from the command prompt
	std::list<std::string>* commandArgsBuffer; 

	// Adding new argument from the command line to the commandArgBuffer
	void AddCommandArg(std::string& argument) const;

	// Picking appropriate command according to the starting command keyword
	CommandType PickCommandType(std::string& commandWord) const;
	
	// Implementing parsed CommandType and parsing secondary arguments to the operation
	void Implement(CommandType commandType, std::list<std::string>& secondaryArguments) const;

	CommandManager();
	~CommandManager();
};

#endif