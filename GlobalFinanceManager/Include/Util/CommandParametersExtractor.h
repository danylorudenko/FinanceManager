#ifndef __COMMAND_PARAMETERS_EXTRACTOR_H__
#define __COMMAND_PARAMETERS_EXTRACTOR_H__

#include <map>
#include <string>
#include <regex>

class CommandParametersExtractor
{
public:
	// Recieves raw parameters string from user
	CommandParametersExtractor(std::string parameters_string);

	// An attempt to get argument contets by the prefix of the argument
	// Parameter to getter should look like "t", not "/t"
	// Method throws std::out_of_range if there is no argumet with passed prefix
	const std::string& TryGetArgument(const std::string& argument_prefix) const;

	// Getting count of the arguments
	const size_t ArgumentsCount() const;

	const std::string& GetPrefix(const int index) const;

protected:
	std::vector<std::string> arguments_prefixes_;
	std::map<std::string, std::string> arguments_map_;
	static const std::regex regex_parameter_;
};

#endif