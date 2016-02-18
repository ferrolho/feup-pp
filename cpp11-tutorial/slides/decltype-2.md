<h2>decltype</h2>

C++ 11
```c++
template <typename Builder>
auto makeAndProcessObject(const Builder& builder) -> decltype(builder.makeObject()) {
	auto val = builder.makeObject();

	// do stuff with val

	return val;
}
```

<br>
<p class="fragment">... so that's why!</p>

<aside class="notes">
</aside>
