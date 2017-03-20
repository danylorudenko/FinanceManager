#include "..\Include\Util\Request\ComplexPredicate\CategoryPredicate.h"

CategoryPredicate::CategoryPredicate(const std::string& category_compared) : AComplexPredicate()
{
	category_compared_ = new std::string(category_compared);
}

CategoryPredicate::~CategoryPredicate()
{
	delete category_compared_;
}

bool CategoryPredicate::IsValid(const FinanceEntry& entry) const
{
	if (*category_compared_ != entry.GetCategory()) {
		return false;
	}

	return next_component_->IsValid(entry);
}