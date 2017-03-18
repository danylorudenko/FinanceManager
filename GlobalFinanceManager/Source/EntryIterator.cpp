#include "..\Include\Util\EntryIterator.h"

EntryIterator::EntryIterator(container* target_container, const Request& request) : 
	target_container_p_(target_container), current_index_(-1)
{
	request_ = new Request(request);
}

EntryIterator::EntryIterator(const EntryIterator& rhs) :
	target_container_p_(rhs.target_container_p_), current_index_(rhs.current_index_)
{
	request_ = new Request(*rhs.request_);
}

EntryIterator::operator bool() const
{
	return current_index_ != -1;
}

EntryIterator& EntryIterator::operator=(const EntryIterator& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	
	target_container_p_ = rhs.target_container_p_;
	current_index_ = rhs.current_index_;
	request_ = new Request(*rhs.request_);

	return *this;
}

bool EntryIterator::operator==(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ < 0 ||
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ == rhs.current_index_;
}

bool EntryIterator::operator!=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ < 0 ||
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ != rhs.current_index_;
}

bool EntryIterator::operator<(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ || 
		current_index_ < 0 || 
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ < rhs.current_index_;
}

bool EntryIterator::operator<=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ < 0 ||
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ <= rhs.current_index_;
}

bool EntryIterator::operator>(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ < 0 ||
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ > rhs.current_index_;
}

bool EntryIterator::operator>=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ < 0 ||
		rhs.current_index_ < 0) {
		return false;
	}

	return current_index_ >= rhs.current_index_;
}

EntryIterator::value_type& EntryIterator::operator*()
{
	if (current_index_ == -1) {
		throw std::length_error("Entry iterator is invalid. Query new one.");
	}

	return (*target_container_p_)[current_index_];
}

EntryIterator& EntryIterator::operator++()
{
	if (current_index_ == -1) {
		throw std::length_error("Entry iterator is invalid. Query new one.");
	}

	int size = target_container_p_->size();
	for (int i = current_index_ + 1; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = -1;
	return *this;
}

EntryIterator EntryIterator::operator++(int)
{
	if (current_index_ == -1) {
		throw std::length_error("Entry iterator is invalid. Query new one.");
	}

	EntryIterator previous_state(*this);

	int size = target_container_p_->size();
	for (int i = current_index_ + 1; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
		}
	}

	current_index_ = -1;
	return previous_state;
}

EntryIterator& EntryIterator::ToBegin()
{
	int size = target_container_p_->size();
	for (int i = 0; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = -1;
	return *this;
}

EntryIterator& EntryIterator::ToEnd()
{
	for (int i = target_container_p_->size(); i >= 0; i--)
	{
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = -1;
	return *this;
}

EntryIterator::~EntryIterator()
{
	delete request_;
}