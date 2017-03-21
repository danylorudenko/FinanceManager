#include "..\Include\Util\Request\ComplexPredicate\AComplexPredicate.h"

AComplexPredicate::AComplexPredicate(AComplexPredicate* next_component) : next_component_(next_component)
{

}

AComplexPredicate::~AComplexPredicate()
{
	delete next_component_;
}

void AComplexPredicate::Decorate(AComplexPredicate* next_component)
{
	if (next_component_ != nullptr) {
		next_component_->Decorate(next_component);
		return;
	}

	next_component_ = next_component;
}