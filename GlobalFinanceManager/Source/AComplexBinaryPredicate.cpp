#include "..\Include\Util\Request\ComplexBinaryPredicate\AComplexBinaryPredicate.h"

AComplexBinaryPredicate::AComplexBinaryPredicate() : next_component_(nullptr)
{

}

AComplexBinaryPredicate::~AComplexBinaryPredicate()
{
	delete next_component_;
}

void AComplexBinaryPredicate::Decorate(AComplexBinaryPredicate* component)
{
	if (next_component_ != nullptr) {
		next_component_->Decorate(component);
		return;
	}

	next_component_ = next_component_;
}