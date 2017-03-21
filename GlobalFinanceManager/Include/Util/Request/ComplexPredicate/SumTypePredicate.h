#ifndef __SUM_TYPE_PREDICATE_H__
#define __SUM_TYPE_PREDICATE_H__

#include "..\..\..\..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"
#include "..\..\..\..\Include\Enums\EntrySumType.h"

class SumTypePredicate : public AComplexPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const;

	SumTypePredicate(const EntrySumType type, AComplexPredicate* next_component = nullptr);

protected:
	const EntrySumType type_;
};

#endif