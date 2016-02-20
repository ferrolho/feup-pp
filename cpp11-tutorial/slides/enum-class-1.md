<h2>enum class</h2>

C++ 03
```c++
enum ball {
	black, white
};

enum cube {
	big, small
};

ball b = black;
cube c = big;

if (b == c) {
	// this is true because they have the same indexes
	cout << "ball black and cube big are the same\n";
}
else
	cout << "ball black and cube big are not the same\n";
```

<aside class="notes">
	C++ 03 does not identify the type of enum and so if we compare different things the result will be always true if the indexes are the same.
</aside>