#include <iostream>

const int* const get_ptr()
{
	int* a_ptr = new int;
	return a_ptr;
}

int ptrmain()
{
	int a;
	int b;

	const int* b_ptr = get_ptr();

	delete b_ptr;

	system("pause");
	return 0;
}