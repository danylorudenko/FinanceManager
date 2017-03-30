#include "..\Include\Entry\EntryModificator\AEntryModificator.h"

AEntryModificator::AEntryModificator(const std::string& content_to_insert) :
	content_to_insert_(content_to_insert), next_component_(nullptr)
{

}

AEntryModificator::~AEntryModificator()
{
	delete next_component_;
}

void AEntryModificator::Decorate(AEntryModificator* next_component) 
{
	if (next_component_ == nullptr) {
		next_component_ = next_component;
	}
	else {
		next_component_->Decorate(next_component);
	}
}