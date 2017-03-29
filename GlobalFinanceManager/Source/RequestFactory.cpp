#include <iostream>

#include "..\Include\Util\Request\RequestFactory.h"
#include "..\Include\Util\CommandParametersExtractor.h"
#include "..\Include\Util\Request\ComplexPredicate\CategoryPredicate.h"
#include "..\Include\Util\Request\ComplexPredicate\DescriptionPredicate.h"
#include "..\Include\Util\Request\ComplexPredicate\SumTypePredicate.h"

const std::string RequestFactory::time_argument_prefix_ = "tm";
const std::string RequestFactory::type_argument_prefix_ = "tp";
const std::string RequestFactory::category_argument_prefix_ = "c";
const std::string RequestFactory::description_argument_prefix_ = "d";
const std::string RequestFactory::sum_argument_prefix_ = "s";

const std::map<std::string, RequestFactory::BuilderDelegate> RequestFactory::builder_delegates_map_ = 
{
	{ RequestFactory::time_argument_prefix_,		RequestFactory::BuildTimeEdgePredicate },
	{ RequestFactory::type_argument_prefix_,		RequestFactory::BuildSumTypePredicate },
	{ RequestFactory::category_argument_prefix_,	RequestFactory::BuildCategoryPredicate },
	{ RequestFactory::description_argument_prefix_, RequestFactory::BuildDescriptionPredicate }
};

Request* RequestFactory::ConstructRequest(std::string& params_string)
{
	// Constructing request with only time decorator
	Request* request = RequestFactory::ConstructTimeRequest(params_string);

	// Removing time argument form the string
	size_t time_prefix_pos = params_string.find(time_argument_prefix_);
	params_string.erase(time_prefix_pos, time_prefix_pos + 2);

	CommandParametersExtractor* arguments_extractor_p = new CommandParametersExtractor(params_string);

	// Decorating request
	const int arguments_count = static_cast<const int>(arguments_extractor_p->ArgumentsCount());
	for (int i = 0; i < arguments_count; i++)
	{
		// Getting prefix string
		const std::string& argument_prefix = arguments_extractor_p->GetPrefix(i);

		// Getting delegate to build ComplexPredicate according to the argument type
		BuilderDelegate builder_delegate = builder_delegates_map_.at(argument_prefix);

		// Calling builder delegate and constructing proper decorator
		AComplexPredicate* predicate = builder_delegate(arguments_extractor_p->TryGetArgument(argument_prefix));

		// Decorating request;
		request->Decorate(predicate);
	}

	delete arguments_extractor_p;
	return request;
}

Request* RequestFactory::ConstructTimeRequest(std::string& params_string)
{
	CommandParametersExtractor* arguments_extractor_p = new CommandParametersExtractor(params_string);

	try {
		const std::string& days_string = arguments_extractor_p->TryGetArgument(time_argument_prefix_);

		AComplexPredicate* time_predicate = BuildTimeEdgePredicate(days_string);

		delete arguments_extractor_p;
		return new Request(dynamic_cast<TimeEdgePredicate*>(time_predicate));
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
		delete arguments_extractor_p;
		return nullptr;
	}
}

AComplexPredicate* RequestFactory::BuildTimeEdgePredicate(const std::string& param)
{
	int days = std::stoi(param);
	return TimeEdgePredicate::LastDays(days);
}

AComplexPredicate* RequestFactory::BuildCategoryPredicate(const std::string& param)
{
	return new CategoryPredicate(param);
}

AComplexPredicate* RequestFactory::BuildDescriptionPredicate(const std::string& param)
{
	return new DescriptionPredicate(param);
}

AComplexPredicate* RequestFactory::BuildSumTypePredicate(const std::string& param)
{
	if (param == "-") {
		return new SumTypePredicate(EntrySumType::Expence);
	}
	else if (param == "+") {
		return new SumTypePredicate(EntrySumType::Income);
	}
	
	return nullptr;
}