#ifndef __DESCRIPTION_PREDICATE_H__
#define __DESCRIPTION_PREDICATE_H__

#include <string>
#include "..\..\..\..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"

class DescriptionPredicate : public AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

	DescriptionPredicate(const std::string& description_compared, AComplexPredicate* next_component = nullptr);
protected:
	std::string description_compared_;
};

#endif