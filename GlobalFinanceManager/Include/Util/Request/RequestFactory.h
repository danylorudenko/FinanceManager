#ifndef __REQUEST_FACTORY_H__
#define __REQUEST_FACTORY_H__

#include <map>
#include "..\..\..\Include\Util\Request\Request.h"

class AComplexPredicate;
class TimeEdgePredicate;
class CategoryPredicate;
class SumTypePredicate;

class RequestFactory
{
public:
	// Constructing request only with time decorator
	// Deleting /tm parameter from the params string
	static Request* ConstructTimeRequest(std::string& params_string);

	// Constructing request with any parameters
	// Params string may be invalid after use
	static Request* ConstructRequest(std::string& params_string);

protected:
	
	static AComplexPredicate* BuildTimeEdgePredicate(const std::string& param);
	static AComplexPredicate* BuildCategoryPredicate(const std::string& param);
	static AComplexPredicate* BuildSumTypePredicate(const std::string& param);
	static AComplexPredicate* BuildDescriptionPredicate(const std::string& param);

	using BuilderDelegate = AComplexPredicate*(*)(const std::string&);

	// Map of AComplexPredicate builders
	const static std::map<std::string, BuilderDelegate> builder_delegates_map_;

	const static std::string time_argument_prefix_;
	const static std::string type_argument_prefix_;
	const static std::string category_argument_prefix_;
	const static std::string description_argument_prefix_;
};

#endif