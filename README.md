# Safe-Pointer
A Smart Pointer Class just for me

Example:

```
#include <iostream>
#include "safe_ptr.hpp"

struct Example
{
	int x = 123, y = 456;
};

int main()
{
	while (true)
	{
		// Example 1
		{
			safe_ptr<Example> Ex;
			std::cout << Ex->x << " " << Ex->y;
		}

		// Example 2
		{
			int* oh_no = new int(1337);
			safe_ptr<int> safe = oh_no;
			std::cout << "\n" << *oh_no;
		} // 'oh_no' gets deleted

		// Example 3
		{
			safe_ptr<size_t> num = 123456789;
			std::cout << "\n" << num;
		}
	}
}
```
