<h2>rvalue reference</h2>

<h4>understanding lvalue and rvalue</h4>

```c++
#include <iostream>
using namespace std;

int main() {
	int x = 3 + 4;
	cout << x << endl;
}
```

<span class="fragment">**x** is an *lvalue* because it persists beyond the expression that defines it</span>

<span class="fragment">**3 + 4** is an *rvalue* because it evaluates to a temporary value that does not persist beyond the expression that defines it</span>
