#ifndef __CATEGORY_BINARY_PREDICATE_H__
#define __CATEGORY_BINARY_PREDICATE_H__

#include "..\..\..\..\Include\Util\Request\ComplexBinaryPredicate\AComplexBinaryPredicate.h"
#include <string>

class CategoryBinaryPredicate : public AComplexBinaryPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

	CategoryBinaryPredicate(const std::string& category_compared);

	virtual ~CategoryBinaryPredicate();

protected:
	const std::string* category_compared_;
};

#endif