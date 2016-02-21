<h2>enum class</h2>

C++ 03
```c++
enum ball { red, blue };
enum cube { big, small };

ball b = red;
cube c = big;

if (b == c) // `true` because `b` and `c` have the same enum indexes
	cout << "a red ball is the same as a big cube (what?)" << endl;
```

C++11
```c++
enum class ball { red, blue };	// notice the class keyword
enum class cube { big, small };

ball b = ball::red;
cube c = cube::big;

if (b == c) // compilation error
	...
```

<aside class="notes">
	C++ 03 does not identify the enum type. If one compares different things, the result will be true if the indexes are the same.

	<br>

	In C++ 11 one can not compare different classes, unless we have a operator of comparison.
</aside>
