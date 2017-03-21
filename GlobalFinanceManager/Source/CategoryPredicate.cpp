#include "..\Include\Util\Request\ComplexPredicate\CategoryPredicate.h"

CategoryPredicate::CategoryPredicate(const std::string& category_compared, AComplexPredicate* next_component) : 
	AComplexPredicate(next_component), category_compared_(category_compared)
{

}

CategoryPredicate::~CategoryPredicate()
{
	
}

bool CategoryPredicate::IsValid(const FinanceEntry& entry) const
{
	if (category_compared_ != entry.GetCategory()) {
		return false;
	}

	if (next_component_ == nullptr) {
		return true;
	}
	return next_component_->IsValid(entry);
}