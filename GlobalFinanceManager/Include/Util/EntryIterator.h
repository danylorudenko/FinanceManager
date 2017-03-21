#ifndef __ENTRY_ITERATOR_H__
#define __ENTRY_ITERATOR_H__

#include "..\..\Include\Managers\MonthFileManager.h"

/*
	Template for accessing finance entries contaiters of type T according to the passed request.
	Request is not responsible for freing memory on member pointers

	If iterator somehow became invalid, it's index is set to (-1) 
	and std::length_exception is thrown.
*/
class EntryIterator
{
public:

	// Type of objects stored in the container
	using container = typename MonthFileManager::container_type;
	using value_type = typename MonthFileManager::container_type::value_type;

	// Iterator is not responsible for freeing the memory
	EntryIterator(container* target_container, const Request* request);

	EntryIterator(const EntryIterator& rhs);

	value_type& operator*();

	EntryIterator& operator=(const EntryIterator& rhs);

	// Is iterator valid to be dereferenced?
	bool IsValid() const;
	
	bool operator==(const EntryIterator& rhs) const;
	bool operator!=(const EntryIterator& rhs) const;
	bool operator<(const EntryIterator& rhs) const;
	bool operator<=(const EntryIterator& rhs) const;
	bool operator>(const EntryIterator& rhs) const;
	bool operator>=(const EntryIterator& rhs) const;

	EntryIterator& operator++();
	EntryIterator& operator--();

	EntryIterator operator+(const int rhs);
	EntryIterator operator-(const int rhs);

	// Should prefer prefix operator, than this to avoid unnecessary stack usage.
	EntryIterator operator++(int);

	// Should prefer prefix operator, than this to avoid unnecessary stack usage.
	EntryIterator operator--(int);

	// Sets iterator's position to the first_valid entry in the target buffer.
	// It is always valid to access except there is no valid entries at all.
	EntryIterator& ToBegin();

	// Sets iterator's position to the (last_valid + 1) entry. So it is not valid to acess.
	// Just like in iterators form STL.
	// This is to make them easy-to-use in comparison operations when looping.
	EntryIterator& ToEnd();

	~EntryIterator();

protected:

	size_t current_index_;

	// This members follows awareness principal of target container, not ownage.
	container* target_container_p_;

	// Points to request to validate entries in target container
	const Request* request_;

};

#endif