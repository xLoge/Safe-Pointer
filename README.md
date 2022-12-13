# Safe-Pointer
Like std::unique_ptr but simpler

Example:

```
#incl
#include <iostream>
#include "safe_ptr.h"

struct Example
{
	int x = 123, y = 456;
};

int main()
{
	// Example 1
	{
		safe_ptr<Example> Ex;
		std::cout << Ex->x << " " << Ex->y;
	}

	// Example 2
	{
		int* oh_no = new int(1337);
		safe_ptr<int> safe(oh_no, true); // (int* ptr, bool reuse) We can assign the 'oh_no' pointer to the safe_ptr
		std::cout << "\n" << *oh_no;
	} // 'oh_no' gets deleted

	// Example 3
	{
		safe_ptr<size_t> num = 123456789;
		std::cout << "\n" << num;
	}
}
```
