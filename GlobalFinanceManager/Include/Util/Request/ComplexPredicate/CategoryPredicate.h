#ifndef __CATEGORY_PREDICATE_H__
#define __CATEGORY_PREDICATE_H__

#include "..\..\..\..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"
#include <string>

class CategoryPredicate : public AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

	CategoryPredicate(const std::string& category_compared, AComplexPredicate* next_component = nullptr);

	virtual ~CategoryPredicate();

protected:
	const std::string category_compared_;
};

#endif