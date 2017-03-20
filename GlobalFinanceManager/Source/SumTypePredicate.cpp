#include "..\Include\Util\Request\ComplexPredicate\SumTypePredicate.h"

bool SumTypePredicate::IsValid(const FinanceEntry& entry) const
{
	if ((type_ == EntrySumType::Income) ? (entry.GetSum() < 0) : (entry.GetSum() > 0))
	{
		return false;
	}

	return next_component_->IsValid(entry);
}

SumTypePredicate::SumTypePredicate(const EntrySumType type) : type_(type)
{

}