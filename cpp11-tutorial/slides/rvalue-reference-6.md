<h2>rvalue reference</h2>

<h4>the new move constructor</h4>

```c++
class GiantVector {
	int size;
	double* elems;

public:
	GiantVector(const GiantVector& vec) { ... } // *COPY* constructor

	// *MOVE* constructor
	GiantVector(GiantVector&& vec) { // notice the non-const &&
		size = vec.size;

		elems = vec.elems;     // move elements from `vec` to `this`
		vec.elems = nullptr;   // update the `vec` content
	}

	~GiantVector() { delete elems; }
}
```

<aside class="notes">
</aside>
