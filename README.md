# Safe-Pointer
A Smart Pointer Class just for me

Example:

```
#include <iostream>
#include "safe_ptr.hpp"

int main()
{
	struct Example
	{
		int x = 123, y = 456;
	};

	// Example 1
	{
		fst::safe_ptr<Example> Ex;
		Ex.init();
		std::cout << Ex->x << " " << Ex->y << std::endl;
	}

	// Example 2
	{
		int* oh_no = new int(1337);
		fst::safe_ptr<int> safe = oh_no;
		std::cout << *oh_no << std::endl;
	}

	// Example 3
	{
		fst::safe_ptr<size_t> num = 123456789;
		std::cout << *num << std::endl;
	}

	// Example 4
	{
		fst::safe_ptr<long long> num = new long long(54321);
		std::cout << *num << std::endl;
	}
}
```
