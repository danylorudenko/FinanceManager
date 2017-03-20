#ifndef __A_COMPLEX_BINARY_PREDICATE_H__
#define __A_COMPLEX_BINARY_PREDICATE_H__

class FinanceEntry;

using FinancePredicate = bool(*)(const FinanceEntry& entry);

class AComplexBinaryPredicate
{
public:
	virtual bool IsValid(const FinanceEntry& entry) const = 0;
	void Decorate(AComplexBinaryPredicate* component);

	
	virtual ~AComplexBinaryPredicate();

protected:
	AComplexBinaryPredicate();

	// Object is responsible for deleting components
	AComplexBinaryPredicate* next_component_;
};

#endif