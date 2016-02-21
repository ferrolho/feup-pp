<h2>static_assert</h2>

C++03
```c++
// library
#include <assert.h>

int* b = NULL;
assert(b != NULL);

cout << "Hello World!\n";

```
Console Message
```text
Assertion `b!=__null' failed.
```

<aside class="notes">
assert is used to abort the program execution if the condition is not verified. This assert can only be used in run-time.
</aside>