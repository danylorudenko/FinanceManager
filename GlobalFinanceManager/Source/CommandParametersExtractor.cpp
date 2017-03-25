#include "..\Include\Util\CommandParametersExtractor.h"
#include <iostream>

const std::regex CommandParametersExtractor::regex_parameter_ = std::regex
(
	"(\\/)"		  // 1
	"([\\S]*)"	  // 2
	"(:)"		  // 3
	"([\\S]*)"	  // 4
);

CommandParametersExtractor::CommandParametersExtractor(std::string parameters_string)
{
	std::smatch result;

	while (std::regex_search(parameters_string, result, regex_parameter_)) {
		arguments_prefixes_.push_back(result[2].str());
		arguments_map_.insert({ result[2].str(), result[4] });

		parameters_string = result.suffix().str();
	}
}

const std::string& CommandParametersExtractor::TryGetArgument(const std::string& argument_prefix) const
{
	return arguments_map_.at(argument_prefix);
}

const size_t CommandParametersExtractor::ArgumentsCount() const
{
	return arguments_prefixes_.size();
}

const std::string& CommandParametersExtractor::GetPrefix(const int index) const
{
	return arguments_prefixes_.at(index);
}