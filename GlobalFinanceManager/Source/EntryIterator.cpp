#include "..\Include\Util\EntryIterator.h"

EntryIterator::EntryIterator(container* target_container, const Request& request) :
	target_container_p_(target_container), current_index_(SIZE_MAX)
{
	request_ = new Request(request);
}

EntryIterator::EntryIterator(const EntryIterator& rhs) :
	target_container_p_(rhs.target_container_p_), current_index_(rhs.current_index_)
{
	request_ = new Request(*rhs.request_);
}

bool EntryIterator::IsValid() const
{
	return current_index_ != SIZE_MAX;
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
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ == rhs.current_index_;
}

bool EntryIterator::operator!=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ != rhs.current_index_;
}

bool EntryIterator::operator<(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ < rhs.current_index_;
}

bool EntryIterator::operator<=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ <= rhs.current_index_;
}

bool EntryIterator::operator>(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ > rhs.current_index_;
}

bool EntryIterator::operator>=(const EntryIterator& rhs) const
{
	if (target_container_p_ != rhs.target_container_p_ ||
		current_index_ == SIZE_MAX ||
		rhs.current_index_ == SIZE_MAX) {
		return false;
	}

	return current_index_ >= rhs.current_index_;
}

EntryIterator::value_type& EntryIterator::operator*()
{
	if (current_index_ == SIZE_MAX) {
		throw std::length_error("Entry iterator is invalid. Query new one.");
	}

	return (*target_container_p_)[current_index_];
}

EntryIterator& EntryIterator::operator++()
{
	if (current_index_ == SIZE_MAX) {
		return *this;
	}

	size_t size = target_container_p_->size();
	for (size_t i = current_index_ + 1; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = SIZE_MAX;
	return *this;
}

EntryIterator& EntryIterator::operator--()
{
	if (current_index_ == SIZE_MAX) {
		return *this;
	}
	
	for (size_t i = current_index_ - 1; i >= 0; i--) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = SIZE_MAX;
	return *this;
}

EntryIterator EntryIterator::operator+(const int rhs)
{
	EntryIterator to_return(*this);

	for (int i = 0; i < rhs; i++)
	{
		++to_return;
	}

	return to_return;
}

EntryIterator EntryIterator::operator-(const int rhs)
{
	EntryIterator to_return(*this);
	
	for (int i = 0; i < rhs; i++)
	{
		--to_return;
	}

	return to_return;
}

EntryIterator EntryIterator::operator--(int)
{
	if (current_index_ == SIZE_MAX) {
		return *this;
	}
	
	EntryIterator previous_state(*this);

	for (size_t i = current_index_ - 1; i >= 0; i--) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return previous_state;
		}
	}

	current_index_ = SIZE_MAX;
	return previous_state;
}

EntryIterator EntryIterator::operator++(int)
{
	if (current_index_ == SIZE_MAX) {
		return *this;
	}
	
	EntryIterator previous_state(*this);

	size_t size = target_container_p_->size();
	for (size_t i = current_index_ + 1; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return previous_state;
		}
	}

	current_index_ = SIZE_MAX;
	return previous_state;
}

EntryIterator& EntryIterator::ToBegin()
{
	size_t size = target_container_p_->size();
	for (size_t i = 0; i < size; i++) {
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i;
			return *this;
		}
	}

	current_index_ = SIZE_MAX;
	return *this;
}

EntryIterator& EntryIterator::ToEnd()
{
	if (target_container_p_->size() == 0) {
		current_index_ = SIZE_MAX;
		return *this;
	}
	
	for (size_t i = target_container_p_->size() - 1; i >= 0; i--)
	{
		if (request_->IsValid((*target_container_p_)[i])) {
			current_index_ = i + 1;
			return *this;
		}
	}

	current_index_ = SIZE_MAX;
	return *this;
}

EntryIterator::~EntryIterator()
{
	delete request_;
}