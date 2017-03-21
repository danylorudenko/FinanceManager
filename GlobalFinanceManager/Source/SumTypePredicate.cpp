#include "..\Include\Util\Request\ComplexPredicate\SumTypePredicate.h"

bool SumTypePredicate::IsValid(const FinanceEntry& entry) const
{
	if ((type_ == EntrySumType::Income) ? (entry.GetSum() < 0) : (entry.GetSum() > 0))
	{
		return false;
	}

	if (next_component_ == nullptr) {
		return true;
	}
	return next_component_->IsValid(entry);
}

SumTypePredicate::SumTypePredicate(const EntrySumType type, AComplexPredicate* next_component) : 
	AComplexPredicate(next_component), type_(type)
{

}