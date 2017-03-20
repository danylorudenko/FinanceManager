#include "..\Include\Util\Request\ComplexBinaryPredicate\CategoryBinaryPredicate.h"

CategoryBinaryPredicate::CategoryBinaryPredicate(const std::string& category_compared) : AComplexBinaryPredicate()
{
	category_compared_ = new std::string(category_compared);
}

CategoryBinaryPredicate::~CategoryBinaryPredicate()
{
	delete category_compared_;
}

bool CategoryBinaryPredicate::IsValid(const FinanceEntry& entry) const
{
	throw std::exception();
}