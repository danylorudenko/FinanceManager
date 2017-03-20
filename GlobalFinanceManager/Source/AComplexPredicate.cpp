#include "..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"

AComplexPredicate::AComplexPredicate() : next_component_(nullptr)
{

}

AComplexPredicate::~AComplexPredicate()
{
	delete next_component_;
}

void AComplexPredicate::Decorate(AComplexPredicate* component)
{
	if (next_component_ != nullptr) {
		next_component_->Decorate(component);
		return;
	}

	next_component_ = next_component_;
}