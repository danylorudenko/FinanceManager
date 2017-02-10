#include <algorithm>
#include "..\Include\Managers\CommandManager.h"
#include <iostream>
#include <cctype>

CommandManager* CommandManager::instance = nullptr; //statacs are initialized in .cpp files

CommandManager::CommandManager()
{
	commandArgsBuffer = new std::list<std::string>;
}

CommandManager::~CommandManager()
{
	delete commandArgsBuffer;
}

CommandManager& CommandManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new CommandManager();
		return *instance;
	}
	else
	{
		return *instance;
	}
}

std::string CommandManager::GetUserCommand()
{
	Instance().commandArgsBuffer->clear();

	std::string commandLine = "";
	std::cout << "$ ";
	std::getline(std::cin, commandLine);

	std::string commandArgument = "";

	for (unsigned int i = 0; i < commandLine.size(); ++i)
	{
		if (i == commandLine.size() - 1)
		{
			commandArgument += commandLine[i];
			AddCommandArg(commandArgument);
		}
		else if (isspace(commandLine[i]))
		{
			AddCommandArg(commandArgument);
			continue;
		}
		else if ((isalpha(commandLine[i]) && islower(commandLine[i])) || commandLine[i] == '_')
		{
			commandArgument += commandLine[i];
			if (i == (commandLine.size() - 1))
			{
				AddCommandArg(commandArgument);
			}
			continue;
		}
		else
		{
			Instance().commandArgsBuffer->clear();
			
			std::cout << "\n\n------- Bad argument! --------\n"
				<< "Type HELP to see all available commands\n"
				<< "Try again\n";
			break;
		}
	}

	if (!(Instance().commandArgsBuffer->empty()))
	{
		std::string firstArg = *(Instance().commandArgsBuffer->begin());
		CommandType currentCommand = Instance().PickCommandType(firstArg);

		Instance().Implement(currentCommand, *commandArgsBuffer);

		return firstArg;
	}

	std::cout << "There were no arguments!" << std::endl;
	return "";
}

void CommandManager::AddCommandArg(std::string& argument) const
{
	Instance().commandArgsBuffer->push_back(argument);
	argument.clear();
}

CommandType CommandManager::PickCommandType(std::string& commandWord) const
{
	for (unsigned int i = 0; i < validCommands.size(); ++i)
	{
		if (validCommands[i] == commandWord)
		{
			return CommandType(i);
		}
	}

	return CommandType::BAD_COMMAND;
}

void CommandManager::Implement(CommandType commandType, std::list<std::string>& secondaryArguments) const
{
	switch (commandType)
	{
	case CommandType::HELP:
		std::cout << "HELP!" << std::endl;
		break;
	case CommandType::DISPLAY_FINANCES:
		std::cout << "DISPLAY_FINANCES!" << std::endl;
		break;
	case CommandType::ADD_SPENDINGS:
		std::cout << "ADD_SPENDINGS!" << std::endl;
		break;
	case CommandType::ADD_INCOME:
		std::cout << "ADD_INCOME!" << std::endl;
		break;
	case CommandType::BAD_COMMAND:
		std::cout << "COMMAND ARGUMENT ERROR" << std::endl;
		break;
	case CommandType::EXIT:
		std::cout << "EXIT!" << std::endl;
		break;
	}
}
