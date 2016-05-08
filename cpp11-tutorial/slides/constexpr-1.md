<h2>constexpr</h2>

<h3>specific example</h3>
```cpp
template<int N>
class list {};

constexpr int sqr1(int arg) { return arg * arg; }

int sqr2(int arg) { return arg * arg; }

const int X = 2;
list<sqr1(X)> mylist1;  // OK: sqr1 is constexpr
list<sqr2(X)> mylist2;  // error: call to non-constexpr function
```