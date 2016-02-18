<h2>lambda functions</h2>

```c++
template<typename func>
void filter(func f, vector<int> vec) {
	for (auto x : vec)
		if (f(x))
			cout << x << " ";
	cout << endl;
}

int main() {
	vector<int> vec = {1, 2, 3, 4, 5};

	filter([](int x) { return x < 4; }, vec);

	int min = 2;
	filter([&](int x) { return min <= x; }, vec);	// note the `[&]`
}
```

output
```text
1 2 3
2 3 4 5
```

<aside class="notes">
</aside>
