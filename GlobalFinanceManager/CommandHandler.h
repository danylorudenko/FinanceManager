#ifndef __COMMAND_HANDLER_H__
#define __COMMAND_HANDLER_H__

#include <list>
#include <string>
#include <array>
#include "Enums\CommandType.h"


class CommandHandler
{

public:
	static CommandHandler& Instance(); // singletone access

	std::string GetUserCommand(); //Recieving list of words in line command.

private:
	const std::array<std::string, 5> validCommands = { "help", "display_finances", "add_income", "add_spendings", "exit" };
	static CommandHandler* instance; //singletone instance

	std::list<std::string>* commandArgs; //list of the command arguments

	void AddCommandArg(std::string& argument) const;

	CommandType PickCommandType(std::string commandWord) const;
	
	void Implement(CommandType commandType, std::list<std::string> secondaryArguments) const;

	CommandHandler();
	~CommandHandler();
};

#endif