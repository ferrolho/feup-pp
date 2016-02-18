<h2>lambda functions</h2>

<h4>std::function</h4>

```c++
#include <functional>
using namespace std;
```

```c++
// declaring `func` (but not defining it!)
function<int ()> func;

// check if we have a function (we don't since we didn't provide one)
if (func)
	func();	// if we did have a function, call it
```

<br>

```c++
vector<string> filter(function<bool (const string&)> func) {

	...

}
```

<aside class="notes">
</aside>
