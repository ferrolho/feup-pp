<h2>enum class</h2>

C++11
```c++
// enum will be interpreted as a class
enum class ball {
	black, white
};

enum class cube {
	big, small
};

ball b = ball::black;
cube c = cube::big;

if (b == c) // compilation error
	cout << "ball black and cube big are the same\n";
else
	cout << "ball black and cube big are not the same\n";
```

<aside class="notes">
	C++11 We can not compare different classes unless we have a operator of comparison. Now we can take advantages of the types in enum.
</aside>