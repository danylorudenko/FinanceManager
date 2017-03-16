#ifndef __BUFFER_ITERATOR_H__
#define __BUFFER_ITERATOR_H__

#include <stdexcept>

/*
	Template for accessing finance entries contaiters of type T according to the passed request.
	Request is copied and stored inside the iterator.

	If iterator somehow became invalid, it's index is set to (-1) 
	and std::length_exception is thrown.
*/
template<typename T>
class EntryIterator
{
public:

	// Type of objects stored in the container T
	using value_type = T::value_type;

	EntryIterator(T* target_containter, const Request& request) :
		target_container_(target_container), current_index_(-1)
	{
		request_ = new Request(request);

		ToBegin();
	}

	EntryIterator(const EntryIterator<T>& rhs)
	{
		target_container_ = rhs.target_container_;
		request_ = new Request(*rhs.request_);
	}

	value_type& operator*() const
	{
		if (current_index_ == -1) {
			throw std::length_error("Entry iterator is invalid. Query new one.");
		}
		
		return (*target_container_)[i];
	}

	EntryIterator<T>& operator++()
	{
		if (current_index_ == -1) {
			throw std::length_error("Entry iterator is invalid. Query new one.");
		}
		
		size_t size = target_container_.size();
		for (int i = current_index_ + 1; i < size; i++) {
			if (request_->IsValid((*target_container_)[i])) {
				current_index_ = i;
				return *this;
			}
		}
	}

	EntryIterator<T> operator++(int)
	{
		if (current_index_ == -1) {
			throw std::length_error("Entry iterator is invalid. Query new one.");
		}
		
		EntryIterator<T> previous_state(*this);

		size_t size = target_container_.size();
		for (int i = current_index_ + 1; i < size; i++) {
			if (request_->IsValid((*target_container_)[i])) {
				current_index_ = i;
			}
		}

		return previous_state;
	}

	EntryIterator<T>& ToBegin()
	{
		size_t size = target_container_.size();
		for (int i = 0; i < size; i++) {
			if (request_->IsValid((*target_container_)[i])) {
				current_index_ = i;
				return *this;
			}
		}

		current_index_ = -1;
		return *this;
	}

	EntryIterator<T>& ToEnd()
	{
		for (size_t i = target_container_.size(); i >= 0; i--)
		{
			if (request_->IsValid((*target_container_)[i])) {
				current_index_ = i;
				return *this;
			}
		}

		current_index_ = -1;
		return *this;
	}

	~EntryIterator()
	{
		delete request_;
	}

private:
	using EntriesBuffer = T;

	int current_index_;
	EntriesBuffer* target_container_;
	Request* request_;

};

#endif