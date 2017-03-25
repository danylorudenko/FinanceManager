#include "..\Include\Util\Request\ComplexPredicate\DescriptionPredicate.h"

DescriptionPredicate::DescriptionPredicate(const std::string& description_compared, AComplexPredicate* next_component) :
	description_compared_(description_compared), AComplexPredicate(next_component)
{

}

bool DescriptionPredicate::IsValid(const FinanceEntry& entry) const
{
	if (description_compared_ != entry.GetDescription()) {
		return false;
	}

	if (next_component_ == nullptr) {
		return true;
	}

	return next_component_->IsValid(entry);
}