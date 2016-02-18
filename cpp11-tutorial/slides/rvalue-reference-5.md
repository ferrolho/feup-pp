<h2>rvalue reference</h2>

```c++
GiantVector createGiantVector() { ... }

void foo(GiantVector vec) { ... }

int main() {
	GiantVector vec = createGiantVector();

	foo(vec);

	foo(createGiantVector());	// ouch! this is terrible
}
```

<aside class="notes">
</aside>
