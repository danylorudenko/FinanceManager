#ifndef __BUFFER_ITERATOR_H__
#define __BUFFER_ITERATOR_H__

#include <stdexcept>

#include "..\..\Include\Managers\MonthFileManager.h"

/*
	Template for accessing finance entries contaiters of type T according to the passed request.
	Request is copied and stored inside the iterator.

	If iterator somehow became invalid, it's index is set to (-1) 
	and std::length_exception is thrown.
*/
class EntryIterator
{
public:

	// Type of objects stored in the container
	using container = typename MonthFileManager::container_type;
	using value_type = typename MonthFileManager::container_type::value_type;

	EntryIterator(container* target_container, const Request& request);

	//EntryIterator(const EntryIterator& rhs);

	value_type& operator*();

	EntryIterator& operator++();

	EntryIterator operator++(int);

	EntryIterator& ToBegin();

	EntryIterator& ToEnd();

	~EntryIterator();

private:

	int current_index_;
	container* target_container_p_;
	Request* request_;

};

#endif